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
#include <stdlib.h>

/* local headers */
#include <common/findgittop.h>

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
int dothedu(const char *path, const char *top, size_t *size){
  char abspath[PATH_MAX+1];
  size_t top_s;
  unsigned int depth=0;

  /* resolve all the junk in the path and copy to abspath */
  if(!realpath(path,abspath))
    return 3;

  top_s=strlen(top);

  /* check that top is the beginning of path */
  if(strncmp(abspath,top,top_s))
    return 2;

  { /* measure the current depth */
    char *i;
    i=&abspath[top_s];
    while(*i)
      if((*(i++))=='/') depth++;
  }

  return dothepath(abspath,top,size,depth);
}

int dothepath(const char *abspath, const char *top, size_t *size, unsigned int depth){
  struct stat st;

  if(stat(abspath,&st))
    return 1;

  if(S_ISDIR(st.st_mode))
    return dothedir(abspath,top,size,depth+1);

  *size=0;
  if(S_ISLNK(st.st_mode)){
    char linkbuf[PATH_MAX+1];
    ssize_t rslt;

    /* read the link */
    rslt=readlink(abspath,linkbuf,PATH_MAX);
    if(rslt>=0)
      linkbuf[rslt]=0;
    else
      linkbuf[0]=0; /* zero len string on err */

    /* if the link is longer than "../"(3)*depth + ".git/annex/objects/"(19)
     * then it might be an annexed file */
    if(rslt>((depth*3)+19)){
      size_t i=0;
      size_t size_pos=0;
      while(i<depth){
	if(strncmp("../",linkbuf+(3*i),3))
	  break; /* break if not same */
	i++;
      }
      if(i!=depth)
	return 0; /* didn't find the right number of "../", bail */
      if(strncmp(".git/annex/objects/",linkbuf+(3*depth),19))
	return 0; /* didn't find the reference the the annex objects dir */
      /* we made it this far, look for the last instance of [-]s[0-9]+[-]
       * and that will be our size */
      for(i=(depth*3)+19;i<rslt-2;i++){
	if(linkbuf[i]=='-' && linkbuf[i+1]=='s' && linkbuf[i+2]>='0' && linkbuf[i+2]<='9')
	  size_pos=i+2;
      }
      if(size_pos!=0){
	i=size_pos;
	while(linkbuf[i]>='0' && linkbuf[i]<='9') i++;
	linkbuf[i]=0;
	*size=(size_t)atoll(&linkbuf[size_pos]);
      }
    }

  }

  return 0;
}

int dothedir(const char *abspath,const char *top,size_t *size,unsigned int depth){
  return 0;
}
