bin_PROGRAMS = gadu

noinst_LTLIBRARIES = libgautils.la

libgautils_la_SOURCES = common/stub.c common/stub.h

gadu_SOURCES = gadu-src/gadu.c gadu-src/opts.c gadu-src/opts.h gadu-src/usage.c \
               gadu-src/usage.h
gadu_LDADD = libgautils.la
gadu_CFLAGS = -I$(srcdir)/gadu-src
