/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#if HAVE_GETOPT_H
#include <getopt.h>
#endif /* HAVE_GETOPT_H */

#include <stdio.h>
#include <stdlib.h>

/* local headers */
#include <opts.h>
#include <usage.h>
#include <common/returncodes.h>

/* Process the command line
 *
 * Does not return on error, version, or help.
 * returns - index of first non-option argument in argv[]
 */
int procopts(int argc, char *argv[]){
  int c;
  int digit_optind = 0;

  opt_progname=argv[0];

  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;

#if HAVE_GETOPT_LONG
    static struct option long_options[] = LONG_OPTS;
    c = getopt_long(argc, argv, SHORT_OPTS,
		    long_options, &option_index);
#else
    c = getopt(argc, argv, SHORT_OPTS);
#endif
    if (c == -1)
      break;

    switch (c) {
    case 'V':
      printf("%s: %s\n", opt_progname, PACKAGE_STRING);
      exit(RTRN_OK);
      break;

    case 'b': /* output bytes */
      opt_bytes=1;
      break;

    case 'h':
      usage();
      exit(RTRN_OK);
      break;

    case 's':
      opt_summarize=1;
      break;

    default:
      fprintf(stderr,"%s: Unknown option %c, use -h for help.\n", opt_progname, c);
    case '?':
      exit(RTRN_ERR_CMDLINE);
      break;
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "%s: You must specify at least one pathname, use -h for help.\n", opt_progname);
    exit(RTRN_ERR_CMDLINE);
  }
  return optind;
}

/* global program options, generally set by the command line */
char *opt_progname; /* holds the program's name */
char *opt_bytes=0; /* whether to output bytes or blocks */
char *opt_summarize=0; /* only display output for command line arguments */
