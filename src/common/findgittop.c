/* Copyright 2012 Steve Seltzer, see COPYING for license */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */
#ifdef HAVE_STRING_H
#include <string.h>
#endif /* HAVE_STRING_H */
#ifdef HAVE_LIMITS_H
#include <limits.h>
#endif /* HAVE_LIMITS_H */
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */
#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif /* HAVE_SYS_STAT_H */
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

/* local headers */
#include <common/findgittop.h>

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
int findgittop(const char *path, char *top, size_t n){
  char curpath[PATH_MAX+1];
  size_t s;

  /* check that the given path does not exceed PATH_MAX */
  s=strlen(path);
  if(s>PATH_MAX)
    return 3;

  /* we start with the given path */
  strncpy(curpath, path, s);

  /* walk the path looking for an element that contains a .git directory */
  while(s>0){
    int rslt=1;
    if(s+5 <= PATH_MAX){
      struct stat st;
      strcat(curpath, "/.git");
      rslt=stat(curpath,&st);
      curpath[s]=0; /* remove the "/.git" */
      if((!rslt) && S_ISDIR(st.st_mode))
	break; /* we found it! */
    }

    /* remove the last element of the path */
    while(s>1 && curpath[s-1]!='/') s--;
    curpath[--s]=0;
  }

  /* special case: relative path */
  if(s==0 && path[0]!='/'){
    struct stat st;
    /* check for ".git" */
    if((!stat(".git",&st)) && S_ISDIR(st.st_mode)){
      curpath[0]='.';
      curpath[1]=0;
      s=1;
    }
  }

  if(s==0)
    return 1;
  if(n < (strlen(curpath)+1))
    return 2;
  strcpy(top,curpath);
  return 0;
}
