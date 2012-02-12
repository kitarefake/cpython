"""distutils.filelist

Provides the FileList class, used for poking about the filesystem
and building lists of files.
"""

import os, re
import fnmatch
from distutils.util import convert_path
from distutils.errors import DistutilsTemplateError, DistutilsInternalError
from distutils import log

class FileList:
    """A list of files built by on exploring the filesystem and filtered by
    applying various patterns to what we find there.

    Instance attributes:
      dir
        directory from which files will be taken -- only used if
        'allfiles' not supplied to constructor
      files
        list of filenames currently being built/filtered/manipulated
      allfiles
        complete list of files under consideration (ie. without any
        filtering applied)
    """

    def __init__(self, warn=None, debug_print=None):
        # ignore argument to FileList, but keep them for backwards
        # compatibility
        self.allfiles = None
        self.files = []

    def set_allfiles(self, allfiles):
        self.allfiles = allfiles

    def findall(self, dir=os.curdir):
        self.allfiles = findall(dir)

    def debug_print(self, msg):
        """Print 'msg' to stdout if the global DEBUG (taken from the
        DISTUTILS_DEBUG environment variable) flag is true.
        """
        from distutils.debug import DEBUG
        if DEBUG:
            print(msg)

    # -- List-like methods ---------------------------------------------

    def append(self, item):
        self.files.append(item)

    def extend(self, items):
        self.files.extend(items)

    def sort(self):
        # Not a strict lexical sort!
        sortable_files = sorted(map(os.path.split, self.files))
        self.files = []
        for sort_tuple in sortable_files:
            self.files.append(os.path.join(*sort_tuple))


    # -- Other miscellaneous utility methods ---------------------------

    def remove_duplicates(self):
        # Assumes list has been sorted!
        for i in range(len(self.files) - 1, 0, -1):
            if self.files[i] == self.files[i - 1]:
                del self.files[i]


    # -- "File template" methods ---------------------------------------

    def _parse_template_line(self, line):
        words = line.split()
        action = words[0]

        patterns = dir = dir_pattern = None

        if action in ('include', 'exclude',
                      'global-include', 'global-exclude'):
            if len(words) < 2:
                raise DistutilsTemplateError(
                      "'%s' expects <pattern1> <pattern2> ..." % action)
            patterns = [convert_path(w) for w in words[1:]]
        elif action in ('recursive-include', 'recursive-exclude'):
            if len(words) < 3:
                raise DistutilsTemplateError(
                      "'%s' expects <dir> <pattern1> <pattern2> ..." % action)
            dir = convert_path(words[1])
            patterns = [convert_path(w) for w in words[2:]]
        elif action in ('graft', 'prune'):
            if len(words) != 2:
                raise DistutilsTemplateError(
                      "'%s' expects a single <dir_pattern>" % action)
            dir_pattern = convert_path(words[1])
        else:
            raise DistutilsTemplateError("unknown action '%s'" % action)

        return (action, patterns, dir, dir_pattern)

    def process_template_line(self, line):
        # Parse the line: split it up, make sure the right number of words
        # is there, and return the relevant words.  'action' is always
        # defined: it's the first word of the line.  Which of the other
        # three are defined depends on the action; it'll be either
        # patterns, (dir and patterns), or (dir_pattern).
        (action, patterns, dir, dir_pattern) = self._parse_template_line(line)

        # OK, now we know that the action is valid and we have the
        # right number of words on the line for that action -- so we
        # can proceed with minimal error-checking.
        if action == 'include':
            self.debug_print("include " + ' '.join(patterns))
            for pattern in patterns:
                if not self.include_pattern(pattern, anchor=1):
                    log.warn("warning: no files found matching '%s'",
                             pattern)

        elif action == 'exclude':
            self.debug_print("exclude " + ' '.join(patterns))
            for pattern in patterns:
                if not self.exclude_pattern(pattern, anchor=1):
                    log.warn(("warning: no previously-included files "
                              "found matching '%s'"), pattern)

        elif action == 'global-include':
            self.debug_print("global-include " + ' '.join(patterns))
            for pattern in patterns:
                if not self.include_pattern(pattern, anchor=0):
                    log.warn(("warning: no files found matching '%s' "
                              "anywhere in distribution"), pattern)

        elif action == 'global-exclude':
            self.debug_print("global-exclude " + ' '.join(patterns))
            for pattern in patterns:
                if not self.exclude_pattern(pattern, anchor=0):
                    log.warn(("warning: no previously-included files matching "
                              "'%s' found anywhere in distribution"),
                             pattern)

        elif action == 'recursive-include':
            self.debug_print("recursive-include %s %s" %
                             (dir, ' '.join(patterns)))
            for pattern in patterns:
                if not self.include_pattern(pattern, prefix=dir):
                    log.warn(("warning: no files found matching '%s' "
                                "under directory '%s'"),
                             pattern, dir)

        elif action == 'recursive-exclude':
            self.debug_print("recursive-exclude %s %s" %
                             (dir, ' '.join(patterns)))
            for pattern in patterns:
                if not self.exclude_pattern(pattern, prefix=dir):
                    log.warn(("warning: no previously-included files matching "
                              "'%s' found under directory '%s'"),
                             pattern, dir)

        elif action == 'graft':
            self.debug_print("graft " + dir_pattern)
            if not self.include_pattern(None, prefix=dir_pattern):
                log.warn("warning: no directories found matching '%s'",
                         dir_pattern)

        elif action == 'prune':
            self.debug_print("prune " + dir_pattern)
            if not self.exclude_pattern(None, prefix=dir_pattern):
                log.warn(("no previously-included directories found "
                          "matching '%s'"), dir_pattern)
        else:
            raise DistutilsInternalError(
                  "this cannot happen: invalid action '%s'" % action)


    # -- Filtering/selection methods -----------------------------------

    def include_pattern(self, pattern, anchor=1, prefix=None, is_regex=0):
        """Select strings (presumably filenames) from 'self.files' that
        match 'pattern', a Unix-style wildcard (glob) pattern.  Patterns
        are not quite the same as implemented by the 'fnmatch' module: '*'
        and '?'  match non-special characters, where "special" is platform-
        dependent: slash on Unix; colon, slash, and backslash on
        DOS/Windows; and colon on Mac OS.

        If 'anchor' is true (the default), then the pattern match is more
        stringent: "*.py" will match "foo.py" but not "foo/bar.py".  If
        'anchor' is false, both of these will match.

        If 'prefix' is supplied, then only filenames starting with 'prefix'
        (itself a pattern) and ending with 'pattern', with anything in between
        them, will match.  'anchor' is ignored in this case.

        If 'is_regex' is true, 'anchor' and 'prefix' are ignored, and
        'pattern' is assumed to be either a string containing a regex or a
        regex object -- no translation is done, the regex is just compiled
        and used as-is.

        Selected strings will be added to self.files.

        Return True if files are found, False otherwise.
        """
        files_found = False
        pattern_re = translate_pattern(pattern, anchor, prefix, is_regex)
        self.debug_print("include_pattern: applying regex r'%s'" %
                         pattern_re.pattern)

        # delayed loading of allfiles list
        if self.allfiles is None:
            self.findall()

        for name in self.allfiles:
            if pattern_re.search(name):
                self.debug_print(" adding " + name)
                self.files.append(name)
                files_found = True
        return files_found


    def exclude_pattern (self, pattern,
                         anchor=1, prefix=None, is_regex=0):
        """Remove strings (presumably filenames) from 'files' that match
        'pattern'.  Other parameters are the same as for
        'include_pattern()', above.
        The list 'self.files' is modified in place.
        Return True if files are found, False otherwise.
        """
        files_found = False
        pattern_re = translate_pattern(pattern, anchor, prefix, is_regex)
        self.debug_print("exclude_pattern: applying regex r'%s'" %
                         pattern_re.pattern)
        for i in range(len(self.files)-1, -1, -1):
            if pattern_re.search(self.files[i]):
                self.debug_print(" removing " + self.files[i])
                del self.files[i]
                files_found = True
        return files_found


# ----------------------------------------------------------------------
# Utility functions

def findall(dir=os.curdir):
    """Find all files under 'dir' and return the list of full filenames
    (relative to 'dir').
    """
    from stat import ST_MODE, S_ISREG, S_ISDIR, S_ISLNK

    list = []
    stack = [dir]
    pop = stack.pop
    push = stack.append

    while stack:
        dir = pop()
        names = os.listdir(dir)

        for name in names:
            if dir != os.curdir:        # avoid the dreaded "./" syndrome
                fullname = os.path.join(dir, name)
            else:
                fullname = name

            # Avoid excess stat calls -- just one will do, thank you!
            stat = os.stat(fullname)
            mode = stat[ST_MODE]
            if S_ISREG(mode):
                list.append(fullname)
            elif S_ISDIR(mode) and not S_ISLNK(mode):
                push(fullname)
    return list


def glob_to_re(pattern):
    """Translate a shell-like glob pattern to a regular expression; return
    a string containing the regex.  Differs from 'fnmatch.translate()' in
    that '*' does not match "special characters" (which are
    platform-specific).
    """
    pattern_re = fnmatch.translate(pattern)

    # '?' and '*' in the glob pattern become '.' and '.*' in the RE, which
    # IMHO is wrong -- '?' and '*' aren't supposed to match slash in Unix,
    # and by extension they shouldn't match such "special characters" under
    # any OS.  So change all non-escaped dots in the RE to match any
    # character except the special characters.
    # XXX currently the "special characters" are just slash -- i.e. this is
    # Unix-only.
    pattern_re = re.sub(r'((?<!\\)(\\\\)*)\.', r'\1[^/]', pattern_re)

    return pattern_re


def translate_pattern(pattern, anchor=1, prefix=None, is_regex=0):
    """Translate a shell-like wildcard pattern to a compiled regular
    expression.  Return the compiled regex.  If 'is_regex' true,
    then 'pattern' is directly compiled to a regex (if it's a string)
    or just returned as-is (assumes it's a regex object).
    """
    if is_regex:
        if isinstance(pattern, str):
            return re.compile(pattern)
        else:
            return pattern

    if pattern:
        pattern_re = glob_to_re(pattern)
    else:
        pattern_re = ''

    if prefix is not None:
        # ditch end of pattern character
        empty_pattern = glob_to_re('')
        prefix_re = (glob_to_re(prefix))[:-len(empty_pattern)]
        # paths should always use / in manifest templates
        pattern_re = "^%s/.*%s" % (prefix_re, pattern_re)
    else:                               # no prefix -- respect anchor flag
        if anchor:
            pattern_re = "^" + pattern_re

    return re.compile(pattern_re)
