#include "Python.h"
#ifdef MS_WINDOWS
#  include <windows.h>
#else
#  include <fcntl.h>
#  ifdef HAVE_SYS_STAT_H
#    include <sys/stat.h>
#  endif
#  ifdef HAVE_LINUX_RANDOM_H
#    include <linux/random.h>
#  endif
#  ifdef HAVE_GETRANDOM
#    include <sys/random.h>
#  elif defined(HAVE_GETRANDOM_SYSCALL)
#    include <sys/syscall.h>
#  endif
#endif

#ifdef Py_DEBUG
int _Py_HashSecret_Initialized = 0;
#else
static int _Py_HashSecret_Initialized = 0;
#endif

#ifdef MS_WINDOWS
static HCRYPTPROV hCryptProv = 0;

static int
win32_urandom_init(int raise)
{
    /* Acquire context */
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL,
                             PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
        goto error;

    return 0;

error:
    if (raise)
        PyErr_SetFromWindowsErr(0);
    else
        Py_FatalError("Failed to initialize Windows random API (CryptoGen)");
    return -1;
}

/* Fill buffer with size pseudo-random bytes generated by the Windows CryptoGen
   API. Return 0 on success, or raise an exception and return -1 on error. */
static int
win32_urandom(unsigned char *buffer, Py_ssize_t size, int raise)
{
    Py_ssize_t chunk;

    if (hCryptProv == 0)
    {
        if (win32_urandom_init(raise) == -1)
            return -1;
    }

    while (size > 0)
    {
        chunk = size > INT_MAX ? INT_MAX : size;
        if (!CryptGenRandom(hCryptProv, (DWORD)chunk, buffer))
        {
            /* CryptGenRandom() failed */
            if (raise)
                PyErr_SetFromWindowsErr(0);
            else
                Py_FatalError("Failed to initialized the randomized hash "
                        "secret using CryptoGen)");
            return -1;
        }
        buffer += chunk;
        size -= chunk;
    }
    return 0;
}

/* Issue #25003: Don't use getentropy() on Solaris (available since
 * Solaris 11.3), it is blocking whereas os.urandom() should not block. */
#elif defined(HAVE_GETENTROPY) && !defined(sun)
#define PY_GETENTROPY 1

/* Fill buffer with size pseudo-random bytes generated by getentropy().
   Return 0 on success, or raise an exception and return -1 on error.

   If fatal is nonzero, call Py_FatalError() instead of raising an exception
   on error. */
static int
py_getentropy(unsigned char *buffer, Py_ssize_t size, int fatal)
{
    while (size > 0) {
        Py_ssize_t len = Py_MIN(size, 256);
        int res;

        if (!fatal) {
            Py_BEGIN_ALLOW_THREADS
            res = getentropy(buffer, len);
            Py_END_ALLOW_THREADS

            if (res < 0) {
                PyErr_SetFromErrno(PyExc_OSError);
                return -1;
            }
        }
        else {
            res = getentropy(buffer, len);
            if (res < 0)
                Py_FatalError("getentropy() failed");
        }

        buffer += len;
        size -= len;
    }
    return 0;
}

#else

#if defined(HAVE_GETRANDOM) || defined(HAVE_GETRANDOM_SYSCALL)
#define PY_GETRANDOM 1

static int
py_getrandom(void *buffer, Py_ssize_t size, int raise)
{
    /* Is getrandom() supported by the running kernel?
     * Need Linux kernel 3.17 or newer, or Solaris 11.3 or newer */
    static int getrandom_works = 1;

    /* getrandom() on Linux will block if called before the kernel has
     * initialized the urandom entropy pool. This will cause Python
     * to hang on startup if called very early in the boot process -
     * see https://bugs.python.org/issue26839. To avoid this, use the
     * GRND_NONBLOCK flag. */
    const int flags = GRND_NONBLOCK;

    char *dest;
    long n;

    if (!getrandom_works)
        return 0;

    dest = buffer;
    while (0 < size) {
#ifdef sun
        /* Issue #26735: On Solaris, getrandom() is limited to returning up
           to 1024 bytes */
        n = Py_MIN(size, 1024);
#else
        n = Py_MIN(size, LONG_MAX);
#endif

        errno = 0;
#ifdef HAVE_GETRANDOM
        if (raise) {
            Py_BEGIN_ALLOW_THREADS
            n = getrandom(dest, n, flags);
            Py_END_ALLOW_THREADS
        }
        else {
            n = getrandom(dest, n, flags);
        }
#else
        /* On Linux, use the syscall() function because the GNU libc doesn't
         * expose the Linux getrandom() syscall yet. See:
         * https://sourceware.org/bugzilla/show_bug.cgi?id=17252 */
        if (raise) {
            Py_BEGIN_ALLOW_THREADS
            n = syscall(SYS_getrandom, dest, n, flags);
            Py_END_ALLOW_THREADS
        }
        else {
            n = syscall(SYS_getrandom, dest, n, flags);
        }
#endif

        if (n < 0) {
            if (errno == ENOSYS) {
                getrandom_works = 0;
                return 0;
            }
            if (errno == EAGAIN) {
                /* If we failed with EAGAIN, the entropy pool was
                 * uninitialized. In this case, we return failure to fall
                 * back to reading from /dev/urandom.
                 *
                 * Note: In this case the data read will not be random so
                 * should not be used for cryptographic purposes. Retaining
                 * the existing semantics for practical purposes. */
                getrandom_works = 0;
                return 0;
            }

            if (errno == EINTR) {
                if (PyErr_CheckSignals()) {
                    if (!raise)
                        Py_FatalError("getrandom() interrupted by a signal");
                    return -1;
                }
                /* retry getrandom() */
                continue;
            }

            if (raise)
                PyErr_SetFromErrno(PyExc_OSError);
            else
                Py_FatalError("getrandom() failed");
            return -1;
        }

        dest += n;
        size -= n;
    }
    return 1;
}
#endif

static struct {
    int fd;
    dev_t st_dev;
    ino_t st_ino;
} urandom_cache = { -1 };


/* Read size bytes from /dev/urandom into buffer.
   Call Py_FatalError() on error. */
static void
dev_urandom_noraise(unsigned char *buffer, Py_ssize_t size)
{
    int fd;
    Py_ssize_t n;

    assert (0 < size);

#ifdef PY_GETRANDOM
    if (py_getrandom(buffer, size, 0) == 1)
        return;
    /* getrandom() is not supported by the running kernel, fall back
     * on reading /dev/urandom */
#endif

    fd = _Py_open_noraise("/dev/urandom", O_RDONLY);
    if (fd < 0)
        Py_FatalError("Failed to open /dev/urandom");

    while (0 < size)
    {
        do {
            n = read(fd, buffer, (size_t)size);
        } while (n < 0 && errno == EINTR);
        if (n <= 0)
        {
            /* stop on error or if read(size) returned 0 */
            Py_FatalError("Failed to read bytes from /dev/urandom");
            break;
        }
        buffer += n;
        size -= n;
    }
    close(fd);
}

/* Read size bytes from /dev/urandom into buffer.
   Return 0 on success, raise an exception and return -1 on error. */
static int
dev_urandom_python(char *buffer, Py_ssize_t size)
{
    int fd;
    Py_ssize_t n;
    struct _Py_stat_struct st;
#ifdef PY_GETRANDOM
    int res;
#endif

    if (size <= 0)
        return 0;

#ifdef PY_GETRANDOM
    res = py_getrandom(buffer, size, 1);
    if (res < 0)
        return -1;
    if (res == 1)
        return 0;
    /* getrandom() is not supported by the running kernel, fall back
     * on reading /dev/urandom */
#endif

    if (urandom_cache.fd >= 0) {
        /* Does the fd point to the same thing as before? (issue #21207) */
        if (_Py_fstat_noraise(urandom_cache.fd, &st)
            || st.st_dev != urandom_cache.st_dev
            || st.st_ino != urandom_cache.st_ino) {
            /* Something changed: forget the cached fd (but don't close it,
               since it probably points to something important for some
               third-party code). */
            urandom_cache.fd = -1;
        }
    }
    if (urandom_cache.fd >= 0)
        fd = urandom_cache.fd;
    else {
        fd = _Py_open("/dev/urandom", O_RDONLY);
        if (fd < 0) {
            if (errno == ENOENT || errno == ENXIO ||
                errno == ENODEV || errno == EACCES)
                PyErr_SetString(PyExc_NotImplementedError,
                                "/dev/urandom (or equivalent) not found");
            /* otherwise, keep the OSError exception raised by _Py_open() */
            return -1;
        }
        if (urandom_cache.fd >= 0) {
            /* urandom_fd was initialized by another thread while we were
               not holding the GIL, keep it. */
            close(fd);
            fd = urandom_cache.fd;
        }
        else {
            if (_Py_fstat(fd, &st)) {
                close(fd);
                return -1;
            }
            else {
                urandom_cache.fd = fd;
                urandom_cache.st_dev = st.st_dev;
                urandom_cache.st_ino = st.st_ino;
            }
        }
    }

    do {
        n = _Py_read(fd, buffer, (size_t)size);
        if (n == -1)
            return -1;
        if (n == 0) {
            PyErr_Format(PyExc_RuntimeError,
                    "Failed to read %zi bytes from /dev/urandom",
                    size);
            return -1;
        }

        buffer += n;
        size -= n;
    } while (0 < size);

    return 0;
}

static void
dev_urandom_close(void)
{
    if (urandom_cache.fd >= 0) {
        close(urandom_cache.fd);
        urandom_cache.fd = -1;
    }
}

#endif

/* Fill buffer with pseudo-random bytes generated by a linear congruent
   generator (LCG):

       x(n+1) = (x(n) * 214013 + 2531011) % 2^32

   Use bits 23..16 of x(n) to generate a byte. */
static void
lcg_urandom(unsigned int x0, unsigned char *buffer, size_t size)
{
    size_t index;
    unsigned int x;

    x = x0;
    for (index=0; index < size; index++) {
        x *= 214013;
        x += 2531011;
        /* modulo 2 ^ (8 * sizeof(int)) */
        buffer[index] = (x >> 16) & 0xff;
    }
}

/* Fill buffer with size pseudo-random bytes from the operating system random
   number generator (RNG). It is suitable for most cryptographic purposes
   except long living private keys for asymmetric encryption.

   Return 0 on success, raise an exception and return -1 on error. */
int
_PyOS_URandom(void *buffer, Py_ssize_t size)
{
    if (size < 0) {
        PyErr_Format(PyExc_ValueError,
                     "negative argument not allowed");
        return -1;
    }
    if (size == 0)
        return 0;

#ifdef MS_WINDOWS
    return win32_urandom((unsigned char *)buffer, size, 1);
#elif defined(PY_GETENTROPY)
    return py_getentropy(buffer, size, 0);
#else
    return dev_urandom_python((char*)buffer, size);
#endif
}

void
_PyRandom_Init(void)
{
    char *env;
    unsigned char *secret = (unsigned char *)&_Py_HashSecret.uc;
    Py_ssize_t secret_size = sizeof(_Py_HashSecret_t);
    Py_BUILD_ASSERT(sizeof(_Py_HashSecret_t) == sizeof(_Py_HashSecret.uc));

    if (_Py_HashSecret_Initialized)
        return;
    _Py_HashSecret_Initialized = 1;

    /*
      Hash randomization is enabled.  Generate a per-process secret,
      using PYTHONHASHSEED if provided.
    */

    env = Py_GETENV("PYTHONHASHSEED");
    if (env && *env != '\0' && strcmp(env, "random") != 0) {
        char *endptr = env;
        unsigned long seed;
        seed = strtoul(env, &endptr, 10);
        if (*endptr != '\0'
            || seed > 4294967295UL
            || (errno == ERANGE && seed == ULONG_MAX))
        {
            Py_FatalError("PYTHONHASHSEED must be \"random\" or an integer "
                          "in range [0; 4294967295]");
        }
        if (seed == 0) {
            /* disable the randomized hash */
            memset(secret, 0, secret_size);
        }
        else {
            lcg_urandom(seed, secret, secret_size);
        }
    }
    else {
#ifdef MS_WINDOWS
        (void)win32_urandom(secret, secret_size, 0);
#elif defined(PY_GETENTROPY)
        (void)py_getentropy(secret, secret_size, 1);
#else
        dev_urandom_noraise(secret, secret_size);
#endif
    }
}

void
_PyRandom_Fini(void)
{
#ifdef MS_WINDOWS
    if (hCryptProv) {
        CryptReleaseContext(hCryptProv, 0);
        hCryptProv = 0;
    }
#elif defined(PY_GETENTROPY)
    /* nothing to clean */
#else
    dev_urandom_close();
#endif
}
