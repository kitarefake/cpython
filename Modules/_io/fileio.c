/* Author: Daniel Stutzbach */

#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "structmember.h"
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#include <stddef.h> /* For offsetof */
#include "_iomodule.h"

/*
 * Known likely problems:
 *
 * - Files larger then 2**32-1
 * - Files with unicode filenames
 * - Passing numbers greater than 2**32-1 when an integer is expected
 * - Making it work on Windows and other oddball platforms
 *
 * To Do:
 *
 * - autoconfify header file inclusion
 */

#ifdef MS_WINDOWS
/* can simulate truncate with Win32 API functions; see file_truncate */
#define HAVE_FTRUNCATE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#if BUFSIZ < (8*1024)
#define SMALLCHUNK (8*1024)
#elif (BUFSIZ >= (2 << 25))
#error "unreasonable BUFSIZ > 64MB defined"
#else
#define SMALLCHUNK BUFSIZ
#endif

/*[clinic input]
module _io
class _io.FileIO "fileio *" "&PyFileIO_Type"
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=1c77708b41fda70c]*/

/*[python input]
class io_ssize_t_converter(CConverter):
    type = 'Py_ssize_t'
    converter = '_PyIO_ConvertSsize_t'
[python start generated code]*/
/*[python end generated code: output=da39a3ee5e6b4b0d input=d0a811d3cbfd1b33]*/

typedef struct {
    PyObject_HEAD
    int fd;
    unsigned int created : 1;
    unsigned int readable : 1;
    unsigned int writable : 1;
    unsigned int appending : 1;
    signed int seekable : 2; /* -1 means unknown */
    unsigned int closefd : 1;
    char finalizing;
    unsigned int blksize;
    PyObject *weakreflist;
    PyObject *dict;
} fileio;

PyTypeObject PyFileIO_Type;

_Py_IDENTIFIER(name);

#define PyFileIO_Check(op) (PyObject_TypeCheck((op), &PyFileIO_Type))

int
_PyFileIO_closed(PyObject *self)
{
    return ((fileio *)self)->fd < 0;
}

/* Because this can call arbitrary code, it shouldn't be called when
   the refcount is 0 (that is, not directly from tp_dealloc unless
   the refcount has been temporarily re-incremented). */
static PyObject *
fileio_dealloc_warn(fileio *self, PyObject *source)
{
    if (self->fd >= 0 && self->closefd) {
        PyObject *exc, *val, *tb;
        PyErr_Fetch(&exc, &val, &tb);
        if (PyErr_WarnFormat(PyExc_ResourceWarning, 1,
                             "unclosed file %R", source)) {
            /* Spurious errors can appear at shutdown */
            if (PyErr_ExceptionMatches(PyExc_Warning))
                PyErr_WriteUnraisable((PyObject *) self);
        }
        PyErr_Restore(exc, val, tb);
    }
    Py_RETURN_NONE;
}

static PyObject *
portable_lseek(int fd, PyObject *posobj, int whence);

static PyObject *portable_lseek(int fd, PyObject *posobj, int whence);

/* Returns 0 on success, -1 with exception set on failure. */
static int
internal_close(fileio *self)
{
    int err = 0;
    int save_errno = 0;
    if (self->fd >= 0) {
        int fd = self->fd;
        self->fd = -1;
        /* fd is accessible and someone else may have closed it */
        if (_PyVerify_fd(fd)) {
            Py_BEGIN_ALLOW_THREADS
            _Py_BEGIN_SUPPRESS_IPH
            err = close(fd);
            if (err < 0)
                save_errno = errno;
            _Py_END_SUPPRESS_IPH
            Py_END_ALLOW_THREADS
        } else {
            save_errno = errno;
            err = -1;
        }
    }
    if (err < 0) {
        errno = save_errno;
        PyErr_SetFromErrno(PyExc_IOError);
        return -1;
    }
    return 0;
}

/*[clinic input]
_io.FileIO.close

Close the file.

A closed file cannot be used for further I/O operations.  close() may be
called more than once without error.
[clinic start generated code]*/

static PyObject *
_io_FileIO_close_impl(fileio *self)
/*[clinic end generated code: output=7737a319ef3bad0b input=f35231760d54a522]*/
{
    PyObject *res;
    PyObject *exc, *val, *tb;
    int rc;
    _Py_IDENTIFIER(close);
    res = _PyObject_CallMethodId((PyObject*)&PyRawIOBase_Type,
                                 &PyId_close, "O", self);
    if (!self->closefd) {
        self->fd = -1;
        return res;
    }
    if (res == NULL)
        PyErr_Fetch(&exc, &val, &tb);
    if (self->finalizing) {
        PyObject *r = fileio_dealloc_warn(self, (PyObject *) self);
        if (r)
            Py_DECREF(r);
        else
            PyErr_Clear();
    }
    rc = internal_close(self);
    if (res == NULL)
        _PyErr_ChainExceptions(exc, val, tb);
    if (rc < 0)
        Py_CLEAR(res);
    return res;
}

static PyObject *
fileio_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    fileio *self;

    assert(type != NULL && type->tp_alloc != NULL);

    self = (fileio *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fd = -1;
        self->created = 0;
        self->readable = 0;
        self->writable = 0;
        self->appending = 0;
        self->seekable = -1;
        self->blksize = 0;
        self->closefd = 1;
        self->weakreflist = NULL;
    }

    return (PyObject *) self;
}

#ifdef O_CLOEXEC
extern int _Py_open_cloexec_works;
#endif

/*[clinic input]
_io.FileIO.__init__
    file as nameobj: object
    mode: str = "r"
    closefd: int(c_default="1") = True
    opener: object = None

Open a file.

The mode can be 'r' (default), 'w', 'x' or 'a' for reading,
writing, exclusive creation or appending.  The file will be created if it
doesn't exist when opened for writing or appending; it will be truncated
when opened for writing.  A FileExistsError will be raised if it already
exists when opened for creating. Opening a file for creating implies
writing so this mode behaves in a similar way to 'w'.Add a '+' to the mode
to allow simultaneous reading and writing. A custom opener can be used by
passing a callable as *opener*. The underlying file descriptor for the file
object is then obtained by calling opener with (*name*, *flags*).
*opener* must return an open file descriptor (passing os.open as *opener*
results in functionality similar to passing None).
[clinic start generated code]*/

static int
_io_FileIO___init___impl(fileio *self, PyObject *nameobj, const char *mode,
                         int closefd, PyObject *opener)
/*[clinic end generated code: output=23413f68e6484bbd input=193164e293d6c097]*/
{
    const char *name = NULL;
    PyObject *stringobj = NULL;
    const char *s;
#ifdef MS_WINDOWS
    Py_UNICODE *widename = NULL;
#endif
    int ret = 0;
    int rwa = 0, plus = 0;
    int flags = 0;
    int fd = -1;
    int fd_is_own = 0;
#ifdef O_CLOEXEC
    int *atomic_flag_works = &_Py_open_cloexec_works;
#elif !defined(MS_WINDOWS)
    int *atomic_flag_works = NULL;
#endif
    struct _Py_stat_struct fdfstat;
    int async_err = 0;

    assert(PyFileIO_Check(self));
    if (self->fd >= 0) {
        if (self->closefd) {
            /* Have to close the existing file first. */
            if (internal_close(self) < 0)
                return -1;
        }
        else
            self->fd = -1;
    }

    if (PyFloat_Check(nameobj)) {
        PyErr_SetString(PyExc_TypeError,
                        "integer argument expected, got float");
        return -1;
    }

    fd = _PyLong_AsInt(nameobj);
    if (fd < 0) {
        if (!PyErr_Occurred()) {
            PyErr_SetString(PyExc_ValueError,
                            "negative file descriptor");
            return -1;
        }
        PyErr_Clear();
    }

#ifdef MS_WINDOWS
    if (PyUnicode_Check(nameobj)) {
        Py_ssize_t length;
        widename = PyUnicode_AsUnicodeAndSize(nameobj, &length);
        if (widename == NULL)
            return -1;
        if (wcslen(widename) != length) {
            PyErr_SetString(PyExc_ValueError, "embedded null character");
            return -1;
        }
    } else
#endif
    if (fd < 0)
    {
        if (!PyUnicode_FSConverter(nameobj, &stringobj)) {
            return -1;
        }
        name = PyBytes_AS_STRING(stringobj);
    }

    s = mode;
    while (*s) {
        switch (*s++) {
        case 'x':
            if (rwa) {
            bad_mode:
                PyErr_SetString(PyExc_ValueError,
                                "Must have exactly one of create/read/write/append "
                                "mode and at most one plus");
                goto error;
            }
            rwa = 1;
            self->created = 1;
            self->writable = 1;
            flags |= O_EXCL | O_CREAT;
            break;
        case 'r':
            if (rwa)
                goto bad_mode;
            rwa = 1;
            self->readable = 1;
            break;
        case 'w':
            if (rwa)
                goto bad_mode;
            rwa = 1;
            self->writable = 1;
            flags |= O_CREAT | O_TRUNC;
            break;
        case 'a':
            if (rwa)
                goto bad_mode;
            rwa = 1;
            self->writable = 1;
            self->appending = 1;
            flags |= O_APPEND | O_CREAT;
            break;
        case 'b':
            break;
        case '+':
            if (plus)
                goto bad_mode;
            self->readable = self->writable = 1;
            plus = 1;
            break;
        default:
            PyErr_Format(PyExc_ValueError,
                         "invalid mode: %.200s", mode);
            goto error;
        }
    }

    if (!rwa)
        goto bad_mode;

    if (self->readable && self->writable)
        flags |= O_RDWR;
    else if (self->readable)
        flags |= O_RDONLY;
    else
        flags |= O_WRONLY;

#ifdef O_BINARY
    flags |= O_BINARY;
#endif

#ifdef MS_WINDOWS
    flags |= O_NOINHERIT;
#elif defined(O_CLOEXEC)
    flags |= O_CLOEXEC;
#endif

    if (fd >= 0) {
        self->fd = fd;
        self->closefd = closefd;
    }
    else {
        self->closefd = 1;
        if (!closefd) {
            PyErr_SetString(PyExc_ValueError,
                "Cannot use closefd=False with file name");
            goto error;
        }

        errno = 0;
        if (opener == Py_None) {
            do {
                Py_BEGIN_ALLOW_THREADS
#ifdef MS_WINDOWS
                if (widename != NULL)
                    self->fd = _wopen(widename, flags, 0666);
                else
#endif
                    self->fd = open(name, flags, 0666);
                Py_END_ALLOW_THREADS
            } while (self->fd < 0 && errno == EINTR &&
                     !(async_err = PyErr_CheckSignals()));

            if (async_err)
                goto error;
        }
        else {
            PyObject *fdobj;

#ifndef MS_WINDOWS
            /* the opener may clear the atomic flag */
            atomic_flag_works = NULL;
#endif

            fdobj = PyObject_CallFunction(opener, "Oi", nameobj, flags);
            if (fdobj == NULL)
                goto error;
            if (!PyLong_Check(fdobj)) {
                Py_DECREF(fdobj);
                PyErr_SetString(PyExc_TypeError,
                        "expected integer from opener");
                goto error;
            }

            self->fd = _PyLong_AsInt(fdobj);
            Py_DECREF(fdobj);
            if (self->fd == -1) {
                goto error;
            }
        }

        fd_is_own = 1;
        if (self->fd < 0) {
            PyErr_SetFromErrnoWithFilenameObject(PyExc_OSError, nameobj);
            goto error;
        }

#ifndef MS_WINDOWS
        if (_Py_set_inheritable(self->fd, 0, atomic_flag_works) < 0)
            goto error;
#endif
    }

    self->blksize = DEFAULT_BUFFER_SIZE;
    if (_Py_fstat(self->fd, &fdfstat) < 0)
        goto error;
#if defined(S_ISDIR) && defined(EISDIR)
    /* On Unix, open will succeed for directories.
       In Python, there should be no file objects referring to
       directories, so we need a check.  */
    if (S_ISDIR(fdfstat.st_mode)) {
        errno = EISDIR;
        PyErr_SetFromErrnoWithFilenameObject(PyExc_IOError, nameobj);
        goto error;
    }
#endif /* defined(S_ISDIR) */
#ifdef HAVE_STRUCT_STAT_ST_BLKSIZE
    if (fdfstat.st_blksize > 1)
        self->blksize = fdfstat.st_blksize;
#endif /* HAVE_STRUCT_STAT_ST_BLKSIZE */

#if defined(MS_WINDOWS) || defined(__CYGWIN__)
    /* don't translate newlines (\r\n <=> \n) */
    _setmode(self->fd, O_BINARY);
#endif

    if (_PyObject_SetAttrId((PyObject *)self, &PyId_name, nameobj) < 0)
        goto error;

    if (self->appending) {
        /* For consistent behaviour, we explicitly seek to the
           end of file (otherwise, it might be done only on the
           first write()). */
        PyObject *pos = portable_lseek(self->fd, NULL, 2);
        if (pos == NULL)
            goto error;
        Py_DECREF(pos);
    }

    goto done;

 error:
    ret = -1;
    if (!fd_is_own)
        self->fd = -1;
    if (self->fd >= 0)
        internal_close(self);

 done:
    Py_CLEAR(stringobj);
    return ret;
}

static int
fileio_traverse(fileio *self, visitproc visit, void *arg)
{
    Py_VISIT(self->dict);
    return 0;
}

static int
fileio_clear(fileio *self)
{
    Py_CLEAR(self->dict);
    return 0;
}

static void
fileio_dealloc(fileio *self)
{
    self->finalizing = 1;
    if (_PyIOBase_finalize((PyObject *) self) < 0)
        return;
    _PyObject_GC_UNTRACK(self);
    if (self->weakreflist != NULL)
        PyObject_ClearWeakRefs((PyObject *) self);
    Py_CLEAR(self->dict);
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *
err_closed(void)
{
    PyErr_SetString(PyExc_ValueError, "I/O operation on closed file");
    return NULL;
}

static PyObject *
err_mode(char *action)
{
    _PyIO_State *state = IO_STATE();
    if (state != NULL)
        PyErr_Format(state->unsupported_operation,
                     "File not open for %s", action);
    return NULL;
}

/*[clinic input]
_io.FileIO.fileno

Return the underlying file descriptor (an integer).
[clinic start generated code]*/

static PyObject *
_io_FileIO_fileno_impl(fileio *self)
/*[clinic end generated code: output=a9626ce5398ece90 input=0b9b2de67335ada3]*/
{
    if (self->fd < 0)
        return err_closed();
    return PyLong_FromLong((long) self->fd);
}

/*[clinic input]
_io.FileIO.readable

True if file was opened in a read mode.
[clinic start generated code]*/

static PyObject *
_io_FileIO_readable_impl(fileio *self)
/*[clinic end generated code: output=640744a6150fe9ba input=a3fdfed6eea721c5]*/
{
    if (self->fd < 0)
        return err_closed();
    return PyBool_FromLong((long) self->readable);
}

/*[clinic input]
_io.FileIO.writable

True if file was opened in a write mode.
[clinic start generated code]*/

static PyObject *
_io_FileIO_writable_impl(fileio *self)
/*[clinic end generated code: output=96cefc5446e89977 input=c204a808ca2e1748]*/
{
    if (self->fd < 0)
        return err_closed();
    return PyBool_FromLong((long) self->writable);
}

/*[clinic input]
_io.FileIO.seekable

True if file supports random-access.
[clinic start generated code]*/

static PyObject *
_io_FileIO_seekable_impl(fileio *self)
/*[clinic end generated code: output=47909ca0a42e9287 input=c8e5554d2fd63c7f]*/
{
    if (self->fd < 0)
        return err_closed();
    if (self->seekable < 0) {
        PyObject *pos = portable_lseek(self->fd, NULL, SEEK_CUR);
        if (pos == NULL) {
            PyErr_Clear();
            self->seekable = 0;
        } else {
            Py_DECREF(pos);
            self->seekable = 1;
        }
    }
    return PyBool_FromLong((long) self->seekable);
}

/*[clinic input]
_io.FileIO.readinto
    buffer: Py_buffer(accept={rwbuffer})
    /

Same as RawIOBase.readinto().
[clinic start generated code]*/

static PyObject *
_io_FileIO_readinto_impl(fileio *self, Py_buffer *buffer)
/*[clinic end generated code: output=b01a5a22c8415cb4 input=4721d7b68b154eaf]*/
{
    Py_ssize_t n;
    int err;

    if (self->fd < 0)
        return err_closed();
    if (!self->readable)
        return err_mode("reading");

    n = _Py_read(self->fd, buffer->buf, buffer->len);
    /* copy errno because PyBuffer_Release() can indirectly modify it */
    err = errno;

    if (n == -1) {
        if (err == EAGAIN) {
            PyErr_Clear();
            Py_RETURN_NONE;
        }
        return NULL;
    }

    return PyLong_FromSsize_t(n);
}

static size_t
new_buffersize(fileio *self, size_t currentsize)
{
    size_t addend;

    /* Expand the buffer by an amount proportional to the current size,
       giving us amortized linear-time behavior.  For bigger sizes, use a
       less-than-double growth factor to avoid excessive allocation. */
    assert(currentsize <= PY_SSIZE_T_MAX);
    if (currentsize > 65536)
        addend = currentsize >> 3;
    else
        addend = 256 + currentsize;
    if (addend < SMALLCHUNK)
        /* Avoid tiny read() calls. */
        addend = SMALLCHUNK;
    return addend + currentsize;
}

/*[clinic input]
_io.FileIO.readall

Read all data from the file, returned as bytes.

In non-blocking mode, returns as much as is immediately available,
or None if no data is available.  Return an empty bytes object at EOF.
[clinic start generated code]*/

static PyObject *
_io_FileIO_readall_impl(fileio *self)
/*[clinic end generated code: output=faa0292b213b4022 input=dbdc137f55602834]*/
{
    struct _Py_stat_struct status;
    Py_off_t pos, end;
    PyObject *result;
    Py_ssize_t bytes_read = 0;
    Py_ssize_t n;
    size_t bufsize;

    if (self->fd < 0)
        return err_closed();
    if (!_PyVerify_fd(self->fd))
        return PyErr_SetFromErrno(PyExc_IOError);

    _Py_BEGIN_SUPPRESS_IPH
#ifdef MS_WINDOWS
    pos = _lseeki64(self->fd, 0L, SEEK_CUR);
#else
    pos = lseek(self->fd, 0L, SEEK_CUR);
#endif
    _Py_END_SUPPRESS_IPH

    if (_Py_fstat_noraise(self->fd, &status) == 0)
        end = status.st_size;
    else
        end = (Py_off_t)-1;

    if (end > 0 && end >= pos && pos >= 0 && end - pos < PY_SSIZE_T_MAX) {
        /* This is probably a real file, so we try to allocate a
           buffer one byte larger than the rest of the file.  If the
           calculation is right then we should get EOF without having
           to enlarge the buffer. */
        bufsize = (size_t)(end - pos + 1);
    } else {
        bufsize = SMALLCHUNK;
    }

    result = PyBytes_FromStringAndSize(NULL, bufsize);
    if (result == NULL)
        return NULL;

    while (1) {
        if (bytes_read >= (Py_ssize_t)bufsize) {
            bufsize = new_buffersize(self, bytes_read);
            if (bufsize > PY_SSIZE_T_MAX || bufsize <= 0) {
                PyErr_SetString(PyExc_OverflowError,
                                "unbounded read returned more bytes "
                                "than a Python bytes object can hold");
                Py_DECREF(result);
                return NULL;
            }

            if (PyBytes_GET_SIZE(result) < (Py_ssize_t)bufsize) {
                if (_PyBytes_Resize(&result, bufsize) < 0)
                    return NULL;
            }
        }

        n = _Py_read(self->fd,
                     PyBytes_AS_STRING(result) + bytes_read,
                     bufsize - bytes_read);

        if (n == 0)
            break;
        if (n == -1) {
            if (errno == EAGAIN) {
                PyErr_Clear();
                if (bytes_read > 0)
                    break;
                Py_DECREF(result);
                Py_RETURN_NONE;
            }
            Py_DECREF(result);
            return NULL;
        }
        bytes_read += n;
        pos += n;
    }

    if (PyBytes_GET_SIZE(result) > bytes_read) {
        if (_PyBytes_Resize(&result, bytes_read) < 0)
            return NULL;
    }
    return result;
}

/*[clinic input]
_io.FileIO.read
    size: io_ssize_t = -1
    /

Read at most size bytes, returned as bytes.

Only makes one system call, so less data may be returned than requested.
In non-blocking mode, returns None if no data is available.
Return an empty bytes object at EOF.
[clinic start generated code]*/

static PyObject *
_io_FileIO_read_impl(fileio *self, Py_ssize_t size)
/*[clinic end generated code: output=42528d39dd0ca641 input=5c6caa5490c13a9b]*/
{
    char *ptr;
    Py_ssize_t n;
    PyObject *bytes;

    if (self->fd < 0)
        return err_closed();
    if (!self->readable)
        return err_mode("reading");

    if (size < 0)
        return _io_FileIO_readall_impl(self);

#ifdef MS_WINDOWS
    /* On Windows, the count parameter of read() is an int */
    if (size > INT_MAX)
        size = INT_MAX;
#endif

    bytes = PyBytes_FromStringAndSize(NULL, size);
    if (bytes == NULL)
        return NULL;
    ptr = PyBytes_AS_STRING(bytes);

    n = _Py_read(self->fd, ptr, size);
    if (n == -1) {
        /* copy errno because Py_DECREF() can indirectly modify it */
        int err = errno;
        Py_DECREF(bytes);
        if (err == EAGAIN) {
            PyErr_Clear();
            Py_RETURN_NONE;
        }
        return NULL;
    }

    if (n != size) {
        if (_PyBytes_Resize(&bytes, n) < 0) {
            Py_CLEAR(bytes);
            return NULL;
        }
    }

    return (PyObject *) bytes;
}

/*[clinic input]
_io.FileIO.write
    b: Py_buffer
    /

Write bytes b to file, return number written.

Only makes one system call, so not all of the data may be written.
The number of bytes actually written is returned.  In non-blocking mode,
returns None if the write would block.
[clinic start generated code]*/

static PyObject *
_io_FileIO_write_impl(fileio *self, Py_buffer *b)
/*[clinic end generated code: output=b4059db3d363a2f7 input=ffbd8834f447ac31]*/
{
    Py_ssize_t n;
    int err;

    if (self->fd < 0)
        return err_closed();
    if (!self->writable)
        return err_mode("writing");

    n = _Py_write(self->fd, b->buf, b->len);
    /* copy errno because PyBuffer_Release() can indirectly modify it */
    err = errno;

    if (n < 0) {
        if (err == EAGAIN) {
            PyErr_Clear();
            Py_RETURN_NONE;
        }
        return NULL;
    }

    return PyLong_FromSsize_t(n);
}

/* XXX Windows support below is likely incomplete */

/* Cribbed from posix_lseek() */
static PyObject *
portable_lseek(int fd, PyObject *posobj, int whence)
{
    Py_off_t pos, res;

#ifdef SEEK_SET
    /* Turn 0, 1, 2 into SEEK_{SET,CUR,END} */
    switch (whence) {
#if SEEK_SET != 0
    case 0: whence = SEEK_SET; break;
#endif
#if SEEK_CUR != 1
    case 1: whence = SEEK_CUR; break;
#endif
#if SEEK_END != 2
    case 2: whence = SEEK_END; break;
#endif
    }
#endif /* SEEK_SET */

    if (posobj == NULL)
        pos = 0;
    else {
        if(PyFloat_Check(posobj)) {
            PyErr_SetString(PyExc_TypeError, "an integer is required");
            return NULL;
        }
#if defined(HAVE_LARGEFILE_SUPPORT)
        pos = PyLong_AsLongLong(posobj);
#else
        pos = PyLong_AsLong(posobj);
#endif
        if (PyErr_Occurred())
            return NULL;
    }

    if (_PyVerify_fd(fd)) {
        Py_BEGIN_ALLOW_THREADS
        _Py_BEGIN_SUPPRESS_IPH
#ifdef MS_WINDOWS
        res = _lseeki64(fd, pos, whence);
#else
        res = lseek(fd, pos, whence);
#endif
        _Py_END_SUPPRESS_IPH
        Py_END_ALLOW_THREADS
    } else
        res = -1;
    if (res < 0)
        return PyErr_SetFromErrno(PyExc_IOError);

#if defined(HAVE_LARGEFILE_SUPPORT)
    return PyLong_FromLongLong(res);
#else
    return PyLong_FromLong(res);
#endif
}

/*[clinic input]
_io.FileIO.seek
    pos: object
    whence: int = 0
    /

Move to new file position and return the file position.

Argument offset is a byte count.  Optional argument whence defaults to
SEEK_SET or 0 (offset from start of file, offset should be >= 0); other values
are SEEK_CUR or 1 (move relative to current position, positive or negative),
and SEEK_END or 2 (move relative to end of file, usually negative, although
many platforms allow seeking beyond the end of a file).

Note that not all file objects are seekable.
[clinic start generated code]*/

static PyObject *
_io_FileIO_seek_impl(fileio *self, PyObject *pos, int whence)
/*[clinic end generated code: output=c976acdf054e6655 input=0439194b0774d454]*/
{
    if (self->fd < 0)
        return err_closed();

    return portable_lseek(self->fd, pos, whence);
}

/*[clinic input]
_io.FileIO.tell

Current file position.

Can raise OSError for non seekable files.
[clinic start generated code]*/

static PyObject *
_io_FileIO_tell_impl(fileio *self)
/*[clinic end generated code: output=ffe2147058809d0b input=807e24ead4cec2f9]*/
{
    if (self->fd < 0)
        return err_closed();

    return portable_lseek(self->fd, NULL, 1);
}

#ifdef HAVE_FTRUNCATE
/*[clinic input]
_io.FileIO.truncate
    size as posobj: object = NULL
    /

Truncate the file to at most size bytes and return the truncated size.

Size defaults to the current file position, as returned by tell().
The current file position is changed to the value of size.
[clinic start generated code]*/

static PyObject *
_io_FileIO_truncate_impl(fileio *self, PyObject *posobj)
/*[clinic end generated code: output=e49ca7a916c176fa input=9026af44686b7318]*/
{
    Py_off_t pos;
    int ret;
    int fd;

    fd = self->fd;
    if (fd < 0)
        return err_closed();
    if (!self->writable)
        return err_mode("writing");

    if (posobj == Py_None || posobj == NULL) {
        /* Get the current position. */
        posobj = portable_lseek(fd, NULL, 1);
        if (posobj == NULL)
            return NULL;
    }
    else {
        Py_INCREF(posobj);
    }

#if defined(HAVE_LARGEFILE_SUPPORT)
    pos = PyLong_AsLongLong(posobj);
#else
    pos = PyLong_AsLong(posobj);
#endif
    if (PyErr_Occurred()){
        Py_DECREF(posobj);
        return NULL;
    }

    Py_BEGIN_ALLOW_THREADS
    _Py_BEGIN_SUPPRESS_IPH
    errno = 0;
#ifdef MS_WINDOWS
    ret = _chsize_s(fd, pos);
#else
    ret = ftruncate(fd, pos);
#endif
    _Py_END_SUPPRESS_IPH
    Py_END_ALLOW_THREADS

    if (ret != 0) {
        Py_DECREF(posobj);
        PyErr_SetFromErrno(PyExc_IOError);
        return NULL;
    }

    return posobj;
}
#endif /* HAVE_FTRUNCATE */

static char *
mode_string(fileio *self)
{
    if (self->created) {
        if (self->readable)
            return "xb+";
        else
            return "xb";
    }
    if (self->appending) {
        if (self->readable)
            return "ab+";
        else
            return "ab";
    }
    else if (self->readable) {
        if (self->writable)
            return "rb+";
        else
            return "rb";
    }
    else
        return "wb";
}

static PyObject *
fileio_repr(fileio *self)
{
    PyObject *nameobj, *res;

    if (self->fd < 0)
        return PyUnicode_FromFormat("<_io.FileIO [closed]>");

    nameobj = _PyObject_GetAttrId((PyObject *) self, &PyId_name);
    if (nameobj == NULL) {
        if (PyErr_ExceptionMatches(PyExc_AttributeError))
            PyErr_Clear();
        else
            return NULL;
        res = PyUnicode_FromFormat(
            "<_io.FileIO fd=%d mode='%s' closefd=%s>",
            self->fd, mode_string(self), self->closefd ? "True" : "False");
    }
    else {
        res = PyUnicode_FromFormat(
            "<_io.FileIO name=%R mode='%s' closefd=%s>",
            nameobj, mode_string(self), self->closefd ? "True" : "False");
        Py_DECREF(nameobj);
    }
    return res;
}

/*[clinic input]
_io.FileIO.isatty

True if the file is connected to a TTY device.
[clinic start generated code]*/

static PyObject *
_io_FileIO_isatty_impl(fileio *self)
/*[clinic end generated code: output=932c39924e9a8070 input=cd94ca1f5e95e843]*/
{
    long res;

    if (self->fd < 0)
        return err_closed();
    Py_BEGIN_ALLOW_THREADS
    _Py_BEGIN_SUPPRESS_IPH
    if (_PyVerify_fd(self->fd))
        res = isatty(self->fd);
    else
        res = 0;
    _Py_END_SUPPRESS_IPH
    Py_END_ALLOW_THREADS
    return PyBool_FromLong(res);
}

static PyObject *
fileio_getstate(fileio *self)
{
    PyErr_Format(PyExc_TypeError,
                 "cannot serialize '%s' object", Py_TYPE(self)->tp_name);
    return NULL;
}

#include "clinic/fileio.c.h"

static PyMethodDef fileio_methods[] = {
    _IO_FILEIO_READ_METHODDEF
    _IO_FILEIO_READALL_METHODDEF
    _IO_FILEIO_READINTO_METHODDEF
    _IO_FILEIO_WRITE_METHODDEF
    _IO_FILEIO_SEEK_METHODDEF
    _IO_FILEIO_TELL_METHODDEF
    _IO_FILEIO_TRUNCATE_METHODDEF
    _IO_FILEIO_CLOSE_METHODDEF
    _IO_FILEIO_SEEKABLE_METHODDEF
    _IO_FILEIO_READABLE_METHODDEF
    _IO_FILEIO_WRITABLE_METHODDEF
    _IO_FILEIO_FILENO_METHODDEF
    _IO_FILEIO_ISATTY_METHODDEF
    {"_dealloc_warn", (PyCFunction)fileio_dealloc_warn, METH_O, NULL},
    {"__getstate__", (PyCFunction)fileio_getstate, METH_NOARGS, NULL},
    {NULL,           NULL}             /* sentinel */
};

/* 'closed' and 'mode' are attributes for backwards compatibility reasons. */

static PyObject *
get_closed(fileio *self, void *closure)
{
    return PyBool_FromLong((long)(self->fd < 0));
}

static PyObject *
get_closefd(fileio *self, void *closure)
{
    return PyBool_FromLong((long)(self->closefd));
}

static PyObject *
get_mode(fileio *self, void *closure)
{
    return PyUnicode_FromString(mode_string(self));
}

static PyGetSetDef fileio_getsetlist[] = {
    {"closed", (getter)get_closed, NULL, "True if the file is closed"},
    {"closefd", (getter)get_closefd, NULL,
        "True if the file descriptor will be closed by close()."},
    {"mode", (getter)get_mode, NULL, "String giving the file mode"},
    {NULL},
};

static PyMemberDef fileio_members[] = {
    {"_blksize", T_UINT, offsetof(fileio, blksize), 0},
    {"_finalizing", T_BOOL, offsetof(fileio, finalizing), 0},
    {NULL}
};

PyTypeObject PyFileIO_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_io.FileIO",
    sizeof(fileio),
    0,
    (destructor)fileio_dealloc,                 /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    (reprfunc)fileio_repr,                      /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    PyObject_GenericGetAttr,                    /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE
        | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_HAVE_FINALIZE,       /* tp_flags */
    _io_FileIO___init____doc__,                 /* tp_doc */
    (traverseproc)fileio_traverse,              /* tp_traverse */
    (inquiry)fileio_clear,                      /* tp_clear */
    0,                                          /* tp_richcompare */
    offsetof(fileio, weakreflist),      /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    fileio_methods,                             /* tp_methods */
    fileio_members,                             /* tp_members */
    fileio_getsetlist,                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    offsetof(fileio, dict),         /* tp_dictoffset */
    _io_FileIO___init__,                        /* tp_init */
    PyType_GenericAlloc,                        /* tp_alloc */
    fileio_new,                                 /* tp_new */
    PyObject_GC_Del,                            /* tp_free */
    0,                                          /* tp_is_gc */
    0,                                          /* tp_bases */
    0,                                          /* tp_mro */
    0,                                          /* tp_cache */
    0,                                          /* tp_subclasses */
    0,                                          /* tp_weaklist */
    0,                                          /* tp_del */
    0,                                          /* tp_version_tag */
    0,                                          /* tp_finalize */
};
