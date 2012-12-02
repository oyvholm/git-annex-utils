/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifndef __FINDGITTOP_H__
#define __FINDGITTOP_H__

/* Find the top directory of the git tree that contains a path.
 *
 * To accomplish this, we walk backwards through the path and look for a .git
 * directory at each level
 *
 * path - the path inside the git tree
 * top - (output) the top of the git tree
 * n - the size of the output var
 * returns:
 *  0 - success
 *  1 - path was not inside a git tree
 *  2 - top was too small
 *  3 - path exceeds PATH_MAX
 */
int findgittop(const char *path, char *top, size_t n);

#endif /* __FINDGITTOP_H__ */
