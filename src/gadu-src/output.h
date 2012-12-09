/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifndef __OUTPUT_H__
#define __OUTPUT_H__

/* print the given size and path */
void printpath(mpz_t size, const char *path);

/* internal funcs */
void prettyprintsize(mpz_t size);

#endif /* __OUTPUT_H__ */
