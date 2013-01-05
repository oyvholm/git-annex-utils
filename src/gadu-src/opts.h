/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_GMP_H
#include <gmp.h>
#endif

#ifndef __OPTS_H__
#define __OPTS_H__

/* process the command line */
int procopts(int argc, char *argv[]);

/* command line options */
#define SHORT_OPTS "0VB:abchkms"
#define LONG_OPTS { \
{"version",        no_argument,       0, 'V'}, \
{"all",            no_argument,       0, 'a'}, \
{"bytes",          no_argument,       0, 'b'}, \
{"block-size",     required_argument, 0, 'B'}, \
{"help",           no_argument,       0,  0 }, \
{"human-readable", no_argument,       0, 'h'}, \
{"null",           no_argument,       0, '0'}, \
{"summarize",      no_argument,       0, 's'}, \
{"total",          no_argument,       0, 'c'}, \
{0,                0,                 0,  0 } \
}

/* program wide options, generally set by the command line */
extern char *opt_progname; /* holds the executable's name */
extern mpz_t opt_blocksize; /* what blocksize to use for counting */
extern char opt_summarize; /* only display output for command line arguments */
extern char opt_humanreadable; /* display output in a "human readable" format */
extern char opt_outputall; /* print totals for all files, not just dirs */
extern char opt_printtotal; /* print total for all arguments */
extern char opt_outputnullsep; /* use a null instead of '\n' at the end of lines */

/* internal funcs */
void setblocksize(const char *arg); /* set the blocksize */

/* internal defines */
/* the maximum number of digits we will process in the blocksize arg */
#define MAX_BLOCKSIZE_ARG_DIGITS 100

#endif /* __OPTS_H__ */
