/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif /* HAVE_LIMITS_H */

/* local headers */
#include <opts.h>
#include <common/returncodes.h>

int main(int argc, char *argv[]){
  int idx_paths; /* index to the first path in argv[] */

  idx_paths=procopts(argc, argv);

  while(idx_paths<argc){
    size_t size;
    dothedu(argv[idx_paths],&size);
    idx_paths++;
  }

  return RTRN_OK;
}
