bin_PROGRAMS = gadu

noinst_LTLIBRARIES = libgautils.la

libgautils_la_SOURCES = common/normalizepath.c common/normalizepath.h \
                        common/findgitdir.c common/findgitdir.h

gadu_SOURCES = gadu-src/gadu.c gadu-src/opts.c gadu-src/opts.h gadu-src/usage.c \
               gadu-src/usage.h common/returncodes.h gadu-src/dothedu.h \
               gadu-src/dothedu.c gadu-src/init.h gadu-src/init.c \
               gadu-src/output.c gadu-src/output.h
gadu_LDADD = libgautils.la
gadu_CFLAGS = -I$(srcdir)/gadu-src
