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
#include <common/findgittop.h>

int main(int argc, char *argv[]){
  int idx_paths; /* index to the first path in argv[] */

  idx_paths=procopts(argc, argv);

  while(idx_paths<argc){
    char top[PATH_MAX+1];
    if(!findgittop(argv[idx_paths],top,PATH_MAX+1)){
      size_t size;
      printf("%s git dir: %s/.git\n",argv[idx_paths],top);
      dothedu(argv[idx_paths],top,&size);
    }
    else
      fprintf(stderr,"%s is not inside a git tree!\n",argv[idx_paths]);
    idx_paths++;
  }

  return RTRN_OK;
}
