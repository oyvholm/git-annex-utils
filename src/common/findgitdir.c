/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif /* HAVE_LIMITS_H */
#ifdef HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */
#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif /* HAVE_SYS_STAT_H */

/* local headers */
#include <common/findgitdir.h>

/* find the depth of the .git dir from the given path
 *
 * path - path to look in
 * returns:
 * 0+ - path depth
 * -1 - .git dir not found
 * -2 - path too long
 */
int findgitdir(const char *path){
  char tmppath[PATH_MAX+1];
  int depth=0;
  int pathisdir=0;
  struct stat st;

  /* check if the path is too long */
  if(strlen(path)+1+5 > PATH_MAX+1)
    return 1; /* path was too long */

  /* the last element is a special case */
  strcpy(tmppath,path); /* copy the given path to our buffer */
  if(!stat(path,&st))/* check if it is a directory */
    if(S_ISDIR(st.st_mode))
      pathisdir=1;
  /* if the last element is not a dir, it doesn't count in the
   * depth and can't contain the .git dir */
  if(!pathisdir)
    droplastpathelement(tmppath);

  /* look for .git dir at each path element */
  while(strlen(tmppath)>0){
    strcat(tmppath,"/.git");
    if(!stat(tmppath,&st)) /* check if path/.git is a directory */
      if(S_ISDIR(st.st_mode))
	return depth; /* if it is we're done! */
    tmppath[strlen(tmppath)-5]=0; /* remove "/.git" */
    droplastpathelement(tmppath);
    depth++;
  }

  /* we didn't find the .git dir */
  return -1;
}
  
/* drop the last element from a given path */
void droplastpathelement(char *path){
  char *i;
  i=path+strlen(path);
  while(i>path && (*i)!='/') i--;
  (*i)=0;
}
