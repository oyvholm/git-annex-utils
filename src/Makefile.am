bin_PROGRAMS = gadu

noinst_LTLIBRARIES = libgautils.la

libgautils_la_SOURCES = common/stub.c common/stub.h

gadu_SOURCES = gadu-src/gadu.c
gadu_LDADD = libgautils.la
gadu_CFLAGS = -Igadu
