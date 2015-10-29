lib_LTLIBRARIES = libhttpresm.la
libhttpresm_la_CPPFLAGS = -I$(top_srcdir)

libhttpresm_la_SOURCES =								\
\
	urihelper.h											\
	urihelper.cpp										\
	resourcemanagertypedefs.h							\
	jsonconverter.h										\
	jsonconverter.cpp									\
	config.h											\
	config.cpp											\
	resourcemanager.h									\
	resourcemanager.cpp									\
	request.h											\
	request.cpp											\
	response.h											\
	response.cpp										\
	httprequesthandler.h								\
	httprequesthandler.cpp								\
	server.h											\
	server.cpp


bin_PROGRAMS=httpresm
httpresm_LDADD = $(top_builddir)/src/libhttpresm.la
httpresm_CPPFLAGS = -I$(top_srcdir)/src
httpresm_SOURCES=main.cpp

