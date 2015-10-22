dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(httpresm, 1.0)


AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX
AC_LANG([C++])
AC_PROG_LIBTOOL

ACLOCAL_AMFLAGS = '-I m4'

AC_SUBST( install_dir, "/usr/share/httpresm/")

AC_MSG_CHECKING([if release version needed])
AC_ARG_ENABLE([release], [ --enable-release 	enable release version],
[ 
	CPPFLAGS="-O3 -Wall -fmessage-length=0 -std=c++11";
	CXXFLAGS="";
	AC_MSG_RESULT([yes]) 
	AC_DEFINE_UNQUOTED( BUILD_DIR, "${install_dir}/build/")
	AC_DEFINE_UNQUOTED( CONFIG_PATH, "${install_dir}/config.json")
	AC_DEFINE_UNQUOTED( INSTALL_DIR, "${install_dir}")
],
[ 
	CPPFLAGS="-O0 -g3 -Wall -fmessage-length=0 -std=c++11";
	CXXFLAGS="";
	AC_MSG_RESULT([no])
	AC_DEFINE( DEBUG) 
	AC_DEFINE_UNQUOTED( BUILD_DIR, "${srcdir}/build/")
	AC_DEFINE_UNQUOTED( SRC_DIR, "${srcdir}/")
	AC_DEFINE_UNQUOTED( CONFIG_PATH, "${srcdir}/config/config.json")
	AC_DEFINE_UNQUOTED( INSTALL_DIR, "${install_dir}/src/")
])

AC_CHECK_LIB([event], [main], [],
[
    echo "libevent failure."
    exit -1
])

AC_CHECK_LIB([pthread], [main], [],
[
    echo "pthread failure."
    exit -1
])

AC_CHECK_LIB([gtest], [main], [],
[
    echo "google test failure."
    exit -1
])

AC_CHECK_LIB([jsoncpp], [main], [],
[ 
	echo "jsoncpp failure." 
	exit -1
])


# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T


AC_PREFIX_DEFAULT( ${install_dir})

AC_CONFIG_MACRO_DIR([m4])


AC_CONFIG_FILES(Makefile
				config/Makefile
				src/Makefile
				test/Makefile
				)
AC_OUTPUT

