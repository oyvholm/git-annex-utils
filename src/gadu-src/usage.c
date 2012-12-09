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
"  -V, --version     print version\n"
"  -B, --block-size  set the block size\n"
"  -b, --bytes       output size in bytes rather than 1024 byte blocks\n"
"  -s, --summarize   display only a total for each argument\n"
"  --help            display this message\n"
"\n");
}
