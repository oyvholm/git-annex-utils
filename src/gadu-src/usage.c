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
"  -B, --block-size      set the block size\n"
"  -a, --all             print counts for all files, not just directories\n"
"  -b, --bytes           output size in bytes rather than 1024 byte blocks\n"
"  -h, --human-readable  print sizes in human readable format (e.g, 1K 234M 2G)\n"
"  -m                    like --block-size=1M\n"
"  -s, --summarize       display only a total for each argument\n"
"  -V, --version         print version\n"
"  --help                display this message\n"
"\n");
}
