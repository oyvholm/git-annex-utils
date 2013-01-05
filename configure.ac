#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([git-annex-utils], [0.04], [pgp@git-annex.mysteryvortex.com])
AM_INIT_AUTOMAKE([dist-zip dist-bzip2 subdir-objects])
AC_CONFIG_SRCDIR([src/gadu-src/gadu.c])
AC_CONFIG_HEADERS([config.h])

#do checks with c++ preproc/compiler/etc...
AC_LANG([C])

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O #required for subdir-objects
#AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# AutoTroll with Qt.
#AT_WITH_QT

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS_ONCE([dirent.h getopt.h limits.h regex.h])
#AC_CHECK_HEADERS([])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_DECLS([PATH_MAX], [],
               [AC_MSG_ERROR([Couln't find PATH_MAX.  This should be defined in limits.h!])],
               [#ifdef HAVE_LIMITS_H
                # include <limits.h>
                #endif
               ])

# Checks for library functions.
AC_CHECK_FUNCS_ONCE([getopt_long])
AC_CHECK_FUNC([regexec],[],[AC_MSG_ERROR([Couldn't find regexec function!])])
#if we got regexec, we should also have regcomp and regfree
AC_CHECK_FUNC([readlink],[],[AC_MSG_ERROR([Couldn't find readlink function!])])
#TODO: someday we could make gmp optional
AC_CHECK_LIB(gmp,__gmpz_init,,[AC_MSG_ERROR([GNU MP not found, see http://gmplib.org/])])
AC_CHECK_HEADERS([gmp.h],[],[AC_MSG_ERROR([[Couldn't find gmp header!]])])

#set the default install dir to ./inst
#AC_PREFIX_DEFAULT([`pwd`/inst])

AC_CONFIG_FILES([Makefile src/Makefile man/gadu.1])
AC_OUTPUT
