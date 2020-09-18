/* Copyright 2012 Steve Seltzer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3 of the License */

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
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */

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
int normalizepath(const char *path, char *npath, size_t npath_size){
  char *start; /* the start of the current section */
  char *end; /* the end of the current section */

  if(strlen(path)+1 > npath_size)
    return 1; /* npath was too small */

  npath[0]=0; /* start with a zero length string */

  /* make absolute path */
  if(path[0]!='/'){
    if(!getcwd(npath,npath_size))
      return 2;
    if(strlen(npath)+2 > npath_size)
      return 1;
    strcat(npath,"/");
  }

  /* concatenate the given path to the buffer */
  if(strlen(path)+strlen(npath)+2 > npath_size)
    return 1; /* npath was too small */
  strcat(npath,path);

  /* walk the path and replace oddities (see comment above) */
  start=npath;
  end=start;
  while(end < (npath+strlen(npath))){
    end=start+1; /* start looking at the next character after the start */

    while(end < (npath+strlen(npath)) && (*end)!='/') end++; /* move end to the next "/" or the end of the path */
    if((end-start == 1 && (!strncmp(start,"/",1))) ||
       (end-start == 2 && (!strncmp(start,"/.",2))) ){
      /* handle current dir in path */
      memmove(start,end,strlen(end)+1);
      end=start;
    }
    else if (end-start == 3 && (!strncmp(start,"/..",3))){ /* handle previous dir in path */
      if(start<=npath){
	*end=0;
	return 3; /* path began "/../", root has no preious dir, return can't stat */
      }
      /* back start up to the previous '/' */
      start--;
      while((*(start)!='/')&&(start>npath)) start--;
      /* remove the "/.." and the element before it */
      memmove(start,end,strlen(end)+1);
      end=start;
    }
    else{ /* handle files and symbolic links */
      char tmp;
      struct stat st;
      tmp=*end; /* save the current end char */
      *end=0;
      if(lstat(npath,&st)) /* stat the path up to the end char */
	return 3; /* couldn't stat path */
      *end=tmp; /* restore the end */

      /* if it is a good link to a direcotry, replace it with the link text */
      if(S_ISLNK(st.st_mode)){
	*end=0;
	if((!stat(npath,&st)) && (S_ISDIR(st.st_mode))){
	  char linkbuf[PATH_MAX+1];
	  ssize_t rslt;

	  *end=tmp; /* restore the end */

	  /* read the link */
	  rslt=readlink(npath,linkbuf,PATH_MAX);
	  if(rslt>=0)
	    linkbuf[rslt]=0;
	  else
	    linkbuf[0]=0; /* zero len string on err */

	  /* check if the path is now too long */
	  if(start-npath+1+strlen(end)+1+strlen(linkbuf)+1 > npath_size)
	    return 1; /* npath was too small */
	  memmove(start+strlen(linkbuf)+1,end,strlen(end));
	  memcpy(start+1,linkbuf,strlen(linkbuf));
	  end=start;
	}
	else{ /* it is not a good link to a directory */
	  *end=tmp; /* restore the end */
	  start=end; /* leave it in the path */
	}
      }
      else /* this element is OK to leave in the path */
	start=end;
    }
  }
  return 0;
}
