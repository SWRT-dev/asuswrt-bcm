# serial 25
# Determine whether we need the chown wrapper.

dnl Copyright (C) 1997-2001, 2003-2005, 2007, 2009-2011 Free Software
dnl Foundation, Inc.

dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

# chown should accept arguments of -1 for uid and gid, and it should
# dereference symlinks.  If it doesn't, arrange to use the replacement
# function.

# From Jim Meyering.

AC_DEFUN_ONCE([gl_FUNC_CHOWN],
[
  AC_REQUIRE([gl_UNISTD_H_DEFAULTS])
  AC_REQUIRE([AC_TYPE_UID_T])
  AC_REQUIRE([AC_FUNC_CHOWN])
  AC_REQUIRE([gl_FUNC_CHOWN_FOLLOWS_SYMLINK])
  AC_CHECK_FUNCS_ONCE([chown fchown])

  dnl mingw lacks chown altogether.
  if test $ac_cv_func_chown = no; then
    HAVE_CHOWN=0
  else
    dnl Some old systems treated chown like lchown.
    if test $gl_cv_func_chown_follows_symlink = no; then
      REPLACE_CHOWN=1
    fi

    dnl Some old systems tried to use uid/gid -1 literally.
    if test $ac_cv_func_chown_works = no; then
      AC_DEFINE([CHOWN_FAILS_TO_HONOR_ID_OF_NEGATIVE_ONE], [1],
        [Define if chown is not POSIX compliant regarding IDs of -1.])
      REPLACE_CHOWN=1
    fi

    dnl Solaris 9 ignores trailing slash.
    dnl FreeBSD 7.2 mishandles trailing slash on symlinks.
    dnl Likewise for AIX 7.1.
    AC_CACHE_CHECK([whether chown honors trailing slash],
      [gl_cv_func_chown_slash_works],
      [touch conftest.file && rm -f conftest.link
       AC_RUN_IFELSE([AC_LANG_PROGRAM([[
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
]], [[    if (symlink ("conftest.file", "conftest.link")) return 1;
          if (chown ("conftest.link/", getuid (), getgid ()) == 0) return 2;
        ]])],
        [gl_cv_func_chown_slash_works=yes],
        [gl_cv_func_chown_slash_works=no],
        [gl_cv_func_chown_slash_works="guessing no"])
      rm -f conftest.link conftest.file])
    if test "$gl_cv_func_chown_slash_works" != yes; then
      AC_DEFINE([CHOWN_TRAILING_SLASH_BUG], [1],
        [Define to 1 if chown mishandles trailing slash.])
      REPLACE_CHOWN=1
    fi

    dnl OpenBSD fails to update ctime if ownership does not change.
    AC_CACHE_CHECK([whether chown always updates ctime],
      [gl_cv_func_chown_ctime_works],
      [AC_RUN_IFELSE([AC_LANG_PROGRAM([[
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
]], [[    struct stat st1, st2;
          if (close (creat ("conftest.file", 0600))) return 1;
          if (stat ("conftest.file", &st1)) return 2;
          sleep (1);
          if (chown ("conftest.file", st1.st_uid, st1.st_gid)) return 3;
          if (stat ("conftest.file", &st2)) return 4;
          if (st2.st_ctime <= st1.st_ctime) return 5;
        ]])],
        [gl_cv_func_chown_ctime_works=yes],
        [gl_cv_func_chown_ctime_works=no],
        [gl_cv_func_chown_ctime_works="guessing no"])
      rm -f conftest.file])
    if test "$gl_cv_func_chown_ctime_works" != yes; then
      AC_DEFINE([CHOWN_CHANGE_TIME_BUG], [1], [Define to 1 if chown fails
        to change ctime when at least one argument was not -1.])
      REPLACE_CHOWN=1
    fi
  fi
])

# Determine whether chown follows symlinks (it should).
AC_DEFUN_ONCE([gl_FUNC_CHOWN_FOLLOWS_SYMLINK],
[
  AC_CACHE_CHECK(
    [whether chown dereferences symlinks],
    [gl_cv_func_chown_follows_symlink],
    [
      AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

        int
        main ()
        {
          int result = 0;
          char const *dangling_symlink = "conftest.dangle";

          unlink (dangling_symlink);
          if (symlink ("conftest.no-such", dangling_symlink))
            abort ();

          /* Exit successfully on a conforming system,
             i.e., where chown must fail with ENOENT.  */
          if (chown (dangling_symlink, getuid (), getgid ()) == 0)
            result |= 1;
          if (errno != ENOENT)
            result |= 2;
          return result;
        }
        ]])],
        [gl_cv_func_chown_follows_symlink=yes],
        [gl_cv_func_chown_follows_symlink=no],
        [gl_cv_func_chown_follows_symlink=yes]
      )
    ]
  )

  if test $gl_cv_func_chown_follows_symlink = no; then
    AC_DEFINE([CHOWN_MODIFIES_SYMLINK], [1],
      [Define if chown modifies symlinks.])
  fi
])
