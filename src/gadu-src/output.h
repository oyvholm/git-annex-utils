/* Copyright 2012 Steve Seltzer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3 of the License */

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
