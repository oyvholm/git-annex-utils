/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#ifdef HAVE_GMP_H
#include <gmp.h>
#endif /* HAVE_GMP_H */
#ifdef HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */
#include <stdio.h>
#include <stdlib.h>

/* local headers */
#include <opts.h>
#include <output.h>

/* print the given size and path */
void printpath(mpz_t size, const char *path){
  mpz_t out;
  if(opt_humanreadable)
    prettyprintsize(size);
  else{
    mpz_init(out);
    mpz_cdiv_q(out,size,opt_blocksize); /* out=size/blocksize (rounded up) */
    mpz_out_str(stdout,10,out);
  }
  printf("\t%s\n",path);
}

#define MULTIPLIERS "KMGTPEZY"
void prettyprintsize(mpz_t size){
  mpz_t tmp;
  char *multipliers=MULTIPLIERS;
  unsigned char i=0;

  /* start out at 1024, we'll divide by this before using the mulitplier */
  mpz_init_set_ui(tmp,1024);
  /* while the multiplier is smaller than the value */
  while(i<strlen(MULTIPLIERS) && mpz_cmp(size,tmp)>=0){
    mpz_mul_ui(tmp,tmp,1024); /* try the next multiplier */
    i++;
  }
  if(i<=0) /* special case for bytes (no multiplier) */
    mpz_out_str(stdout,10,size);
  else{
    /* go back to the largest multiplier smaller than the value */
    mpz_fdiv_q_ui(tmp,tmp,1024);
    i--;
    mpz_mul_ui(size,size,10); /* multiply by 10 for 1 decimal place */
    mpz_cdiv_q(tmp,size,tmp); /* tmp=size/multiplier (rounded up) */
    mpz_fdiv_q_ui(size,size,10); /* put the size back */

    /* if value is less than 10, print the decimal */
    if(mpz_cmp_ui(tmp,100)<0){
      unsigned long out;
      out=mpz_get_ui(tmp);
      printf("%lu.%lu%c",out/10,out%10,multipliers[i]);
    }
    else{ /* divide of the decimal and print the value */
      mpz_cdiv_q_ui(tmp,tmp,10);
      mpz_out_str(stdout,10,tmp); /* print the digits */
      putchar(multipliers[i]); /* print the multiplier char */
    }
  }
  mpz_clear(tmp);
}