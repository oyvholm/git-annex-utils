/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifndef __NORMALIZEPATH_H__
#define __NORMALIZEPATH_H__

/* normalize the give path, resolve symlinks, remove "//" "/./" "/../",
 * make the path aboslute
 *
 * path - path to normalize
 * npath - space to fill with normalized path
 * npath_size - size of space
 *
 * returns:
 * 0 - success
 * 1 - npath_size was too small
 * 2 - couldn't get current directory
 * 3 - couldn't stat part of the path (npath contains that part)
 */
int normalizepath(const char *path, char *npath, size_t npath_size);

#endif /* __NORMALIZEPATH_H__ */
