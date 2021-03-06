#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([oshmpi-testsuite], [1.0])

AC_CONFIG_AUX_DIR(confdb)
AC_CONFIG_MACRO_DIR(confdb)

echo "Running configure for OSHMPI tests"
AM_INIT_AUTOMAKE([-Wall -Werror -Wno-portability-recursive silent-rules foreign 1.12.3 subdir-objects])

AC_CONFIG_HEADER([include/osmtestconf.h])

# Non-verbose make
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_ARG_WITH(shmem, [AC_HELP_STRING([--with-shmem[=DIR|default]],
                [Use the specified SHMEM installation; Header file shmem.h should be in 
                dir/include, and oshcc should be in dir/bin. Use the in-package oshmpi by default])]
                ,,with_shmem=default)

if test "X${with_shmem}" = "Xdefault" ; then
  # note that the default definition of bindir is 
  #    '${exec_prefix}/bin'
  # so even if prefix is set, exec prefix is not until
  # the very last moment (i.e., not here). 
  if test "X$exec_prefix" = "XNONE" ; then
      saveExec_prefix=$exec_prefix
      if test "X$prefix" = "XNONE" ; then
          # Use the default
          exec_prefix=$ac_default_prefix
      else
          exec_prefix=$prefix
      fi
      # Evaluate with the current setting of exec_prefix
      eval oshmpibindir=${bindir}
      exec_prefix=$saveExec_prefix
  else
      eval oshmpibindir=${bindir}
  fi

  OSHCC=$oshmpibindir/oshcc
else
  OSHCC="${with_shmem}/bin/oshcc"
fi
AC_SUBST(OSHCC)

#if test ! -f "${OSHCC}" ; then
#    AC_MSG_ERROR([unable to find "${OSHCC}" script.])
#fi

# Running C compiler tests
PAC_PROG_CC

# not using libtool for the test suite, so no LT_INIT.  Instead, test here
# for Library programs
AC_PROG_RANLIB
AM_PROG_AR

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_RESTRICT
AC_C_INLINE

# check for attribute support
PAC_C_GNU_ATTRIBUTE

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
