AC_PREREQ(2.61)
AC_INIT([libsimplelog], m4_esyscmd_s([dpkg-parsechangelog | sed -n 's/^Version: //p']), [])
AM_INIT_AUTOMAKE([dist-bzip2 -Wall])
LT_INIT

PACKAGE_VERSION_CURRENT=`echo "$PACKAGE_VERSION" | sed 's/\(@<:@@<:@:digit:@:>@@:>@\+\)\.\(@<:@@<:@:digit:@:>@@:>@\+\)\.\(@<:@@<:@:digit:@:>@@:>@\+\)/\1/' `
PACKAGE_VERSION_REVISION=`echo "$PACKAGE_VERSION" | sed 's/\(@<:@@<:@:digit:@:>@@:>@\+\)\.\(@<:@@<:@:digit:@:>@@:>@\+\)\.\(@<:@@<:@:digit:@:>@@:>@\+\)/\2/' `
PACKAGE_VERSION_AGE=`echo "$PACKAGE_VERSION" | sed 's/\(@<:@@<:@:digit:@:>@@:>@\+\)\.\(@<:@@<:@:digit:@:>@@:>@\+\)\.\(@<:@@<:@:digit:@:>@@:>@\+\)/\3/' `
AC_SUBST(PACKAGE_VERSION_CURRENT)
AC_SUBST(PACKAGE_VERSION_REVISION)
AC_SUBST(PACKAGE_VERSION_AGE)

AC_MSG_CHECKING([whether this is a Git repository])
PACKAGE_GITREVISION=`git describe --tags --always HEAD 2>/dev/null`
which git > /dev/null; \
if test $? -ne 0 || test "x$PACKAGE_GITREVISION" = "x"; then
	PACKAGE_GITREVISION="`cat $srcdir/GITREVISION`-cached"
	AC_MSG_RESULT([no, using stored version info: $PACKAGE_GITREVISION])
else
	echo $PACKAGE_GITREVISION > $srcdir/GITREVISION
	AC_MSG_RESULT([yes, current version info: $PACKAGE_GITREVISION])
fi
AC_SUBST(PACKAGE_GITREVISION)
AC_DEFINE_UNQUOTED([PACKAGE_GITREVISION],["$PACKAGE_GITREVISION"],[Package version with Git revision info])

AC_CONFIG_SRCDIR([src/libsimplelog.c])
AC_CONFIG_HEADERS([config.h])

# Check for options.
####################

# Checks for programs.
######################
AC_PROG_CC
AC_PROG_CPP
AM_PROG_CC_C_O # per product options in Makefile.am

# Checks for libraries.
#######################

# Checks for header files.
##########################
AC_CHECK_HEADERS([string.h sys/time.h])
AC_HEADER_TIME


# Checks for typedefs, structures, and compiler characteristics.
################################################################
AC_C_CONST

#AC_STRUCT_TM
# This macro is obsolescent, as time.h defines struct tm in current systems. New
# programs need not use this macro.
# source: http://www.gnu.org/software/autoconf/manual/autoconf-2.67/html_node/Particular-Structures.html#index-AC_005fSTRUCT_005fTM-685


# Checks for library functions.
###############################
AC_CHECK_FUNCS([gettimeofday])
AC_FUNC_VPRINTF

# AC_FUNC_STRFTIME
# This macro is obsolescent, as no current systems require the intl library for
# strftime. New programs need not use this macro.
# source: http://www.gnu.org/software/autoconf/manual/autoconf-2.67/html_node/Particular-Functions.html#AC_FUNC_STRFTIME


# Output
########
AC_CONFIG_FILES([
	Makefile
	include/Makefile
	src/Makefile
	test/Makefile
	${PACKAGE_NAME}.pc
	])
AC_OUTPUT

echo "
--------------------------------------------------------------------------------
${PACKAGE_NAME} version ${PACKAGE_VERSION} (${PACKAGE_GITREVISION})

 Prefix:       '${prefix}'
 C Compiler:   '${CC} ${CFLAGS} ${CPPFLAGS}'
 Libraries:    '${LIBS}'
--------------------------------------------------------------------------------
"
