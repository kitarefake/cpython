import unittest
from test import test_support
import subprocess
import sys
import signal
import os
import tempfile
import time

mswindows = (sys.platform == "win32")

#
# Depends on the following external programs: Python
#

if mswindows:
    SETBINARY = ('import msvcrt; msvcrt.setmode(sys.stdout.fileno(), '
                                                'os.O_BINARY);')
else:
    SETBINARY = ''

class ProcessTestCase(unittest.TestCase):
    def mkstemp(self):
        """wrapper for mkstemp, calling mktemp if mkstemp is not available"""
        if hasattr(tempfile, "mkstemp"):
            return tempfile.mkstemp()
        else:
            fname = tempfile.mktemp()
            return os.open(fname, os.O_RDWR|os.O_CREAT), fname

    #
    # Generic tests
    #
    def test_call_seq(self):
        """call() function with sequence argument"""
        rc = subprocess.call([sys.executable, "-c",
                              "import sys; sys.exit(47)"])
        self.assertEqual(rc, 47)

    def test_call_kwargs(self):
        """call() function with keyword args"""
        newenv = os.environ.copy()
        newenv["FRUIT"] = "banana"
        rc = subprocess.call([sys.executable, "-c",
                          'import sys, os;' \
                          'sys.exit(os.getenv("FRUIT")=="banana")'],
                        env=newenv)
        self.assertEqual(rc, 1)

    def test_stdin_none(self):
        """.stdin is None when not redirected"""
        p = subprocess.Popen([sys.executable, "-c", 'print "banana"'],
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.wait()
        self.assertEqual(p.stdin, None)

    def test_stdout_none(self):
        """.stdout is None when not redirected"""
        p = subprocess.Popen([sys.executable, "-c", 'print "banana"'],
                         stdin=subprocess.PIPE, stderr=subprocess.PIPE)
        p.wait()
        self.assertEqual(p.stdout, None)

    def test_stderr_none(self):
        """.stderr is None when not redirected"""
        p = subprocess.Popen([sys.executable, "-c", 'print "banana"'],
                         stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        p.wait()
        self.assertEqual(p.stderr, None)

    def test_executable(self):
        """executable"""
        p = subprocess.Popen(["somethingyoudonthave",
                              "-c", "import sys; sys.exit(47)"],
                             executable=sys.executable)
        p.wait()
        self.assertEqual(p.returncode, 47)

    def test_stdin_pipe(self):
        """stdin redirection"""
        p = subprocess.Popen([sys.executable, "-c",
                         'import sys; sys.exit(sys.stdin.read() == "pear")'],
                        stdin=subprocess.PIPE)
        p.stdin.write("pear")
        p.stdin.close()
        p.wait()
        self.assertEqual(p.returncode, 1)

    def test_stdin_filedes(self):
        """stdin is set to open file descriptor"""
        tf = tempfile.TemporaryFile()
        d = tf.fileno()
        os.write(d, "pear")
        os.lseek(d, 0, 0)
        p = subprocess.Popen([sys.executable, "-c",
                         'import sys; sys.exit(sys.stdin.read() == "pear")'],
                         stdin=d)
        p.wait()
        self.assertEqual(p.returncode, 1)

    def test_stdin_fileobj(self):
        """stdin is set to open file object"""
        tf = tempfile.TemporaryFile()
        tf.write("pear")
        tf.seek(0)
        p = subprocess.Popen([sys.executable, "-c",
                         'import sys; sys.exit(sys.stdin.read() == "pear")'],
                         stdin=tf)
        p.wait()
        self.assertEqual(p.returncode, 1)

    def test_stdout_pipe(self):
        """stdout redirection"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys; sys.stdout.write("orange")'],
                         stdout=subprocess.PIPE)
        self.assertEqual(p.stdout.read(), "orange")

    def test_stdout_filedes(self):
        """stdout is set to open file descriptor"""
        tf = tempfile.TemporaryFile()
        d = tf.fileno()
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys; sys.stdout.write("orange")'],
                         stdout=d)
        p.wait()
        os.lseek(d, 0, 0)
        self.assertEqual(os.read(d, 1024), "orange")

    def test_stdout_fileobj(self):
        """stdout is set to open file object"""
        tf = tempfile.TemporaryFile()
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys; sys.stdout.write("orange")'],
                         stdout=tf)
        p.wait()
        tf.seek(0)
        self.assertEqual(tf.read(), "orange")

    def test_stderr_pipe(self):
        """stderr redirection"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys; sys.stderr.write("strawberry")'],
                         stderr=subprocess.PIPE)
        self.assertEqual(p.stderr.read(), "strawberry")

    def test_stderr_filedes(self):
        """stderr is set to open file descriptor"""
        tf = tempfile.TemporaryFile()
        d = tf.fileno()
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys; sys.stderr.write("strawberry")'],
                         stderr=d)
        p.wait()
        os.lseek(d, 0, 0)
        self.assertEqual(os.read(d, 1024), "strawberry")

    def test_stderr_fileobj(self):
        """stderr is set to open file object"""
        tf = tempfile.TemporaryFile()
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys; sys.stderr.write("strawberry")'],
                         stderr=tf)
        p.wait()
        tf.seek(0)
        self.assertEqual(tf.read(), "strawberry")

    def test_stdout_stderr_pipe(self):
        """capture stdout and stderr to the same pipe"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys;' \
                          'sys.stdout.write("apple");' \
                          'sys.stdout.flush();' \
                          'sys.stderr.write("orange")'],
                         stdout=subprocess.PIPE,
                         stderr=subprocess.STDOUT)
        self.assertEqual(p.stdout.read(), "appleorange")

    def test_stdout_stderr_file(self):
        """capture stdout and stderr to the same open file"""
        tf = tempfile.TemporaryFile()
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys;' \
                          'sys.stdout.write("apple");' \
                          'sys.stdout.flush();' \
                          'sys.stderr.write("orange")'],
                         stdout=tf,
                         stderr=tf)
        p.wait()
        tf.seek(0)
        self.assertEqual(tf.read(), "appleorange")

    def test_cwd(self):
        """cwd"""
        tmpdir = os.getenv("TEMP", "/tmp")
        tmpdir = os.path.realpath(tmpdir)
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;' \
                          'sys.stdout.write(os.getcwd())'],
                         stdout=subprocess.PIPE,
                         cwd=tmpdir)
        self.assertEqual(p.stdout.read(), tmpdir)

    def test_env(self):
        """env"""
        newenv = os.environ.copy()
        newenv["FRUIT"] = "orange"
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;' \
                          'sys.stdout.write(os.getenv("FRUIT"))'],
                         stdout=subprocess.PIPE,
                         env=newenv)
        self.assertEqual(p.stdout.read(), "orange")

    def test_communicate(self):
        """communicate()"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;' \
                          'sys.stderr.write("pineapple");' \
                          'sys.stdout.write(sys.stdin.read())'],
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
        (stdout, stderr) = p.communicate("banana")
        self.assertEqual(stdout, "banana")
        self.assertEqual(stderr, "pineapple")

    def test_communicate_returns(self):
        """communicate() should return None if no redirection is active"""
        p = subprocess.Popen([sys.executable, "-c",
                              "import sys; sys.exit(47)"])
        (stdout, stderr) = p.communicate()
        self.assertEqual(stdout, None)
        self.assertEqual(stderr, None)

    def test_communicate_pipe_buf(self):
        """communicate() with writes larger than pipe_buf"""
        # This test will probably deadlock rather than fail, if
        # communicate() does not work properly.
        x, y = os.pipe()
        if mswindows:
            pipe_buf = 512
        else:
            pipe_buf = os.fpathconf(x, "PC_PIPE_BUF")
        os.close(x)
        os.close(y)
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;'
                          'sys.stdout.write(sys.stdin.read(47));' \
                          'sys.stderr.write("xyz"*%d);' \
                          'sys.stdout.write(sys.stdin.read())' % pipe_buf],
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
        string_to_write = "abc"*pipe_buf
        (stdout, stderr) = p.communicate(string_to_write)
        self.assertEqual(stdout, string_to_write)

    def test_writes_before_communicate(self):
        """stdin.write before communicate()"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;' \
                          'sys.stdout.write(sys.stdin.read())'],
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE)
        p.stdin.write("banana")
        (stdout, stderr) = p.communicate("split")
        self.assertEqual(stdout, "bananasplit")
        self.assertEqual(stderr, "")

    def test_universal_newlines(self):
        """universal newlines"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;' + SETBINARY +
                          'sys.stdout.write("line1\\n");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("line2\\r");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("line3\\r\\n");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("line4\\r");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("\\nline5");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("\\nline6");'],
                         stdout=subprocess.PIPE,
                         universal_newlines=1)
        stdout = p.stdout.read()
        if hasattr(open, 'newlines'):
            # Interpreter with universal newline support
            self.assertEqual(stdout,
                             "line1\nline2\nline3\nline4\nline5\nline6")
        else:
            # Interpreter without universal newline support
            self.assertEqual(stdout,
                             "line1\nline2\rline3\r\nline4\r\nline5\nline6")

    def test_universal_newlines_communicate(self):
        """universal newlines through communicate()"""
        p = subprocess.Popen([sys.executable, "-c",
                          'import sys,os;' + SETBINARY +
                          'sys.stdout.write("line1\\n");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("line2\\r");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("line3\\r\\n");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("line4\\r");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("\\nline5");'
                          'sys.stdout.flush();'
                          'sys.stdout.write("\\nline6");'],
                         stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                         universal_newlines=1)
        (stdout, stderr) = p.communicate()
        if hasattr(open, 'newlines'):
            # Interpreter with universal newline support
            self.assertEqual(stdout,
                             "line1\nline2\nline3\nline4\nline5\nline6")
        else:
            # Interpreter without universal newline support
            self.assertEqual(stdout, "line1\nline2\rline3\r\nline4\r\nline5\nline6")

    def test_no_leaking(self):
        """Make sure we leak no resources"""
        for i in range(1026):
            p = subprocess.Popen([sys.executable, "-c",
                    "import sys;sys.stdout.write(sys.stdin.read())"],
                    stdin=subprocess.PIPE,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.PIPE)
            data = p.communicate("lime")[0]
            self.assertEqual(data, "lime")


    def test_list2cmdline(self):
        """list2cmdline"""

        self.assertEqual(subprocess.list2cmdline(['a b c', 'd', 'e']),
                         '"a b c" d e')
        self.assertEqual(subprocess.list2cmdline(['ab"c', '\\', 'd']),
                         'ab\\"c \\ d')
        self.assertEqual(subprocess.list2cmdline(['a\\\\\\b', 'de fg', 'h']),
                         'a\\\\\\b "de fg" h')
        self.assertEqual(subprocess.list2cmdline(['a\\"b', 'c', 'd']),
                         'a\\\\\\"b c d')
        self.assertEqual(subprocess.list2cmdline(['a\\\\b c', 'd', 'e']),
                         '"a\\\\b c" d e')
        self.assertEqual(subprocess.list2cmdline(['a\\\\b\\ c', 'd', 'e']),
                         '"a\\\\b\\ c" d e')


    def test_poll(self):
        """poll"""
        p = subprocess.Popen([sys.executable,
                          "-c", "import time; time.sleep(4)"])
        while p.poll() == None:
            sys.stdout.write(".")
            sys.stdout.flush()
            time.sleep(0.5)
        # Subsequent invocations should just return the returncode
        self.assertEqual(p.poll(), 0)


    def test_wait(self):
        """wait"""
        p = subprocess.Popen([sys.executable,
                          "-c", "import time; time.sleep(2)"])
        self.assertEqual(p.wait(), 0)
        # Subsequent invocations should just return the returncode
        self.assertEqual(p.wait(), 0)

    #
    # POSIX tests
    #
    if not mswindows:
        def test_exceptions(self):
            """catched & re-raised exceptions"""
            try:
                p = subprocess.Popen([sys.executable, "-c", ""],
                                 cwd="/this/path/does/not/exist")
            except OSError, e:
                # The attribute child_traceback should contain "os.chdir"
                # somewhere.
                self.assertNotEqual(e.child_traceback.find("os.chdir"), -1)
            else:
                self.fail("Expected OSError")

        def test_run_abort(self):
            """returncode handles signal termination"""
            p = subprocess.Popen([sys.executable,
                                  "-c", "import os; os.abort()"])
            p.wait()
            self.assertEqual(-p.returncode, signal.SIGABRT)

        def test_preexec(self):
            """preexec function"""
            p = subprocess.Popen([sys.executable, "-c",
                              'import sys,os;' \
                              'sys.stdout.write(os.getenv("FRUIT"))'],
                             stdout=subprocess.PIPE,
                             preexec_fn=lambda: os.putenv("FRUIT", "apple"))
            self.assertEqual(p.stdout.read(), "apple")

        def test_close_fds(self):
            """close_fds"""
            # Make sure we have some fds open
            os.pipe()
            p = subprocess.Popen([sys.executable, "-c",
                              'import sys,os;' \
                              'sys.stdout.write(str(os.dup(0)))'],
                             stdout=subprocess.PIPE, close_fds=1)
            # When all fds are closed, the next free fd should be 3.
            self.assertEqual(p.stdout.read(), "3")

        def test_args_string(self):
            """args is a string"""
            f, fname = self.mkstemp()
            os.write(f, "#!/bin/sh\n")
            os.write(f, "exec %s -c 'import sys; sys.exit(47)'\n" %
                        sys.executable)
            os.close(f)
            os.chmod(fname, 0700)
            p = subprocess.Popen(fname)
            p.wait()
            self.assertEqual(p.returncode, 47)
            os.remove(fname)

        def test_invalid_args(self):
            """invalid arguments should raise ValueError"""
            self.assertRaises(ValueError, subprocess.call,
                              [sys.executable,
                               "-c", "import sys; sys.exit(47)"],
                              startupinfo=47)
            self.assertRaises(ValueError, subprocess.call,
                              [sys.executable,
                               "-c", "import sys; sys.exit(47)"],
                              creationflags=47)

        def test_shell_sequence(self):
            """Run command through the shell (sequence)"""
            newenv = os.environ.copy()
            newenv["FRUIT"] = "apple"
            p = subprocess.Popen(["echo $FRUIT"], shell=1,
                                 stdout=subprocess.PIPE,
                                 env=newenv)
            self.assertEqual(p.stdout.read().strip(), "apple")

        def test_shell_string(self):
            """Run command through the shell (string)"""
            newenv = os.environ.copy()
            newenv["FRUIT"] = "apple"
            p = subprocess.Popen("echo $FRUIT", shell=1,
                                 stdout=subprocess.PIPE,
                                 env=newenv)
            self.assertEqual(p.stdout.read().strip(), "apple")

        def test_call_string(self):
            """call() function with string argument on UNIX"""
            f, fname = self.mkstemp()
            os.write(f, "#!/bin/sh\n")
            os.write(f, "exec %s -c 'import sys; sys.exit(47)'\n" %
                        sys.executable)
            os.close(f)
            os.chmod(fname, 0700)
            rc = subprocess.call(fname)
            self.assertEqual(rc, 47)


    #
    # Windows tests
    #
    if mswindows:
        def test_startupinfo(self):
            """startupinfo argument"""
            # We uses hardcoded constants, because we do not want to
            # depend on win32all.
            STARTF_USESHOWWINDOW = 1
            SW_MAXIMIZE = 3
            startupinfo = subprocess.STARTUPINFO()
            startupinfo.dwFlags = STARTF_USESHOWWINDOW
            startupinfo.wShowWindow = SW_MAXIMIZE
            # Since Python is a console process, it won't be affected
            # by wShowWindow, but the argument should be silently
            # ignored
            subprocess.call([sys.executable, "-c", "import sys; sys.exit(0)"],
                        startupinfo=startupinfo)

        def test_creationflags(self):
            """creationflags argument"""
            CREATE_NEW_CONSOLE = 16
            subprocess.call(sys.executable +
                                ' -c "import time; time.sleep(2)"',
                            creationflags=CREATE_NEW_CONSOLE)

        def test_invalid_args(self):
            """invalid arguments should raise ValueError"""
            self.assertRaises(ValueError, subprocess.call,
                              [sys.executable,
                               "-c", "import sys; sys.exit(47)"],
                              preexec_fn=lambda: 1)
            self.assertRaises(ValueError, subprocess.call,
                              [sys.executable,
                               "-c", "import sys; sys.exit(47)"],
                              close_fds=True)

        def test_shell_sequence(self):
            """Run command through the shell (sequence)"""
            newenv = os.environ.copy()
            newenv["FRUIT"] = "physalis"
            p = subprocess.Popen(["set"], shell=1,
                                 stdout=subprocess.PIPE,
                                 env=newenv)
            self.assertNotEqual(p.stdout.read().find("physalis"), -1)

        def test_shell_string(self):
            """Run command through the shell (string)"""
            newenv = os.environ.copy()
            newenv["FRUIT"] = "physalis"
            p = subprocess.Popen("set", shell=1,
                                 stdout=subprocess.PIPE,
                                 env=newenv)
            self.assertNotEqual(p.stdout.read().find("physalis"), -1)

        def test_call_string(self):
            """call() function with string argument on Windows"""
            rc = subprocess.call(sys.executable +
                                 ' -c "import sys; sys.exit(47)"')
            self.assertEqual(rc, 47)


def test_main():
    test_support.run_unittest(ProcessTestCase)

if __name__ == "__main__":
    test_main()
