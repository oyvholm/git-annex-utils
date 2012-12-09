/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifndef __DOTHEDU_H__
#define __DOTHEDU_H__

/* Walk through the directories and tally up all annexed file sizes
 *
 * To accomplish this, we walk through the directories looking for symlinks
 * that point to the .git/annex/... directory and then tally up the size
 * from them.
 *
 * path - the path inside the git tree
 * top - (output) the top of the git tree
 * n - the size of the output var
 * returns:
 *  0 - success
 *  1 - couldn't stat something
 *  2 - top was not the beginning of path
 *  3 - realpath failed for some reason
 *  4 - couldn't open a dir in the path
 */
int dothedu(const char *path, unsigned int depth);

/* internal funcs */
int dothepath(const char *path, mpz_t size, int output, unsigned int depth);
int dothedir(const char *path, mpz_t size, int output, unsigned int depth);
void printpath(mpz_t size, const char *path);

#endif /* __DOTHEDU_H__ */
