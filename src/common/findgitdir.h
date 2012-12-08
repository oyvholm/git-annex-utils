/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifndef __FINDGITDIR_H__
#define __FINDGITDIR_H__

/* find the depth of the .git dir from the given path
 *
 * path - path to look in
 * returns:
 * 0+ - path depth
 * -1 - .git dir not found
 * -2 - path too long
 */
int findgitdir(const char *path);

/* internal funcs */
void droplastpathelement(char *path); /* drop the last element from a given path */

#endif /* __FINDGITDIR_H__ */
