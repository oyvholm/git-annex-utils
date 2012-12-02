/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifndef __OPTS_H__
#define __OPTS_H__

/* process the command line */
int procopts(int argc, char *argv[]);

/* command line options */
#define SHORT_OPTS "Vh"
#define LONG_OPTS { \
{"version", no_argument,       0, 'V'}, \
{"help",    no_argument,       0, 'h'}, \
{0,         0,                 0,  0 } \
}

/* program wide options, generally set by the command line */
extern char *opt_progname; /* holds the executable's name */

#endif /* __OPTS_H__ */
