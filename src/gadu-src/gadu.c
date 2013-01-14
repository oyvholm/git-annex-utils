/* Copyright 2012 Steve Seltzer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3 of the License */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif /* HAVE_LIMITS_H */
#ifdef HAVE_GMP_H
#include <gmp.h>
#endif /* HAVE_GMP_H */

/* local headers */
#include <init.h>
#include <opts.h>
#include <common/returncodes.h>
#include <common/normalizepath.h>
#include <common/findgitdir.h>
#include <output.h>

int main(int argc, char *argv[]){
  int idx_paths; /* index to the first path in argv[] */
  int retval=RTRN_OK;
  char *defaultpath=".";
  mpz_t size; /* used by dothedu, contains the size of the path given after a call */
  mpz_t total; /* holds the total size for --total */

  /* setup vars, etc... */
  init(argc, argv);
  /* process command line */
  idx_paths=procopts(argc, argv);

  /* if there was no path arg, fake the default path as the arg */
  if(idx_paths>=argc){
    argv=&defaultpath;
    argc=1;
    idx_paths=0;
  }

  mpz_init(size); /* init the size var, we are going to use it */
  if(opt_printtotal)
    mpz_init_set_ui(total,0); /* init the total var, we are going to use it */

  while(idx_paths<argc){
    char path[PATH_MAX+1]={};
    int depth;

    /* first normalize the path */
    switch(normalizepath(argv[idx_paths],path,PATH_MAX+1)){
    case 1:
      fprintf(stderr,"%s: path too long error while normalizing '%s'\n",opt_progname,argv[idx_paths]);
      retval|=RTRN_ERR_PATHTOOLONG;
      break;
    case 2:
      fprintf(stderr,"%s: unable to obtain current directory while normalizing '%s'\n",opt_progname,argv[idx_paths]);
      retval|=RTRN_ERR_BADCWD;
      break;
    case 3:
      fprintf(stderr,"%s: couldn't stat '%s' while normalizing '%s'\n",opt_progname,path,argv[idx_paths]);
      retval|=RTRN_ERR_FILE;
      break;
    case 0:
      depth=findgitdir(path);
      if(depth>=0){
	int rslt;
	switch(rslt=dothedu(argv[idx_paths],depth,size)){
	case 0:
	  if(opt_printtotal && rslt==0)
	    mpz_add(total,total,size);
	  break;
	case 1:
	case 2:
	  fprintf(stderr,"%s: There was an error accessing a file while calculating the size of '%s'\n",opt_progname,argv[idx_paths]);
	  retval|=RTRN_ERR_FILE;
	  break;
	case 3:
	  fprintf(stderr,"%s: path too long error while calculating the size of '%s'\n",opt_progname,argv[idx_paths]);
	  retval|=RTRN_ERR_PATHTOOLONG;
	  break;
	default:
	  fprintf(stderr,"%s: unknown error while calculating the size of '%s'\n",opt_progname,argv[idx_paths]);
	  retval|=RTRN_ERR_INTERNAL;
	}
      }
      else{
	switch(depth){
	case -2:
	  fprintf(stderr,"%s: path too long error while searching for a .git directory under '%s'\n",opt_progname,path);
	  retval|=RTRN_ERR_PATHTOOLONG;
	  break;
	case -1:
	  fprintf(stderr,"%s: couldn't find a .git directory under '%s'\n",opt_progname,path);
	  retval|=RTRN_ERR_NOTGITREPO;
	  break;
	default:
	  fprintf(stderr,"%s: an unknown error occurred while searching for a .git directory under '%s'\n",opt_progname,path);
	  retval|=RTRN_ERR_INTERNAL;
	}
      }
      break;
    default:
      fprintf(stderr,"%s: unknown error while normalizing '%s'\n",opt_progname,argv[idx_paths]);
      retval|=RTRN_ERR_INTERNAL;
    }
    idx_paths++;
  }

  if(opt_printtotal){
    printpath(total,"total");
    mpz_clear(total);
  }

  mpz_clear(size); /* free the size var */

  return retval;
}
