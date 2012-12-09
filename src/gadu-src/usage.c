/* Copyright 2012 Steve Seltzer, see COPYING for license
 *
 * Display the usage */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>

/* local headers */
#include <opts.h>

void usage(){
  printf("usage: %s [options] <path> [<path>...]\n",opt_progname);
  printf(
"  -V, --version    print version\n"
"  -b, --bytes      output size in bytes rather than 512 byte blocks\n"
"  -s, --summarize  display only a total for each argument\n"
"  --help           display this message\n"
"\n");
}
