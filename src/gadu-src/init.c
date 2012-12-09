/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_GMP_H
#include <gmp.h>
#endif

/* local headers */
#include <opts.h>

/* program initialization, set vars, etc... */
void init(int argc, char *argv[]){
  opt_progname=argv[0]; /* save our program name */

  /* initialize the blocksize var */
  mpz_init_set_ui(opt_blocksize,1024);
}
