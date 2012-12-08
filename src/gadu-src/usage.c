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
"  -V, --version   Print version\n"
"  -h, --help      Display this message\n"
"  -b, --bytes     Output size in bytes rather than 512 byte blocks\n"
"\n");
}
