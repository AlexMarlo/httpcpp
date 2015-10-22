bin_PROGRAMS=httpresmtest
lib_LTLIBRARIES = libhttpresmtest.la
libhttpresmtest_la_CPPFLAGS = -I$(top_srcdir)/src -fPIC
libhttpresmtest_la_SOURCES =								\
\
	configtest.h											\
	jsonconvertertest.h										\
	resourcemanagertest.h
	
httpresmtest_LDADD = $(top_builddir)/test/libhttpresmtest.la $(top_builddir)/src/libhttpresm.la
httpresmtest_CPPFLAGS = -I$(top_srcdir)/src -I$(top_srcdir)/test

httpresmtest_SOURCES=main.cpp