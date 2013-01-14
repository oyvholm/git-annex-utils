/* Copyright 2012 Steve Seltzer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 3 of the License */

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
#ifdef HAVE_REGEX_H
# include <regex.h>
#endif /* HAVE_REGEX_H */
#ifdef HAVE_DIRENT_H
# include <dirent.h>
#endif /* HAVE_DIRENT_H */
#ifdef HAVE_GMP_H
#include <gmp.h>
#endif /* HAVE_GMP_H */
#include <stdio.h>
#include <stdlib.h>

/* local headers */
#include <opts.h>
#include <common/returncodes.h>
#include <dothedu.h>
#include <output.h>

/* Walk through the directories and tally up all annexed file sizes
 *
 * To accomplish this, we walk through the directories looking for symlinks
 * that point to the .git/annex/... directory and then tally up the size
 * from them.
 *
 * path - the path inside the git tree
 * depth - the depth into the path of the .git dir
 * size - (output) the calculated size of the path
 * returns:
 *  0 - success
 *  1 - couldn't stat something
 *  2 - couldn't open a dir in the path
 *  3 - path size exceeds PATH_MAX
 */
int dothedu(const char *path, unsigned int depth, mpz_t size){
  int retval;
  retval=dothepath(path,size,1,depth);
  return retval;
}

/* handle a path
 *
 * path - the path to handle
 * size - place to report back the file/dir size
 * cmdline - this path came from the command line
 * depth - the depth of the .git dir from the path
 *
 * returns:
 * 0 - success
 * 1 - couldn't stat something
 */
int dothepath(const char *path, mpz_t size, int cmdline, unsigned int depth){
  struct stat st;
  regex_t regex;
  regmatch_t regmatch;
  char *p;

  if(lstat(path,&st)){
    fprintf(stderr,"%s: warning - couldn't stat %s\n",opt_progname,path);
    return 1; /* couldn't stat a path */
  }

  if(S_ISDIR(st.st_mode))
    return dothedir(path,size,cmdline|(!opt_summarize),depth+(cmdline?0:1));

  mpz_set_ui(size,0); /* we're handling it, start with a zero size */

  do{
    if(S_ISLNK(st.st_mode)){
      char linkbuf[PATH_MAX+1];
      ssize_t rslt;
      unsigned int i;

      /* read the link */
      rslt=readlink(path,linkbuf,PATH_MAX);
      if(rslt>=0)
	linkbuf[rslt]=0;
      else
	linkbuf[0]=0; /* zero len string on err */

      /* look for the annexed link structure
       * must be "../" * depth followed by ".git/annex/objects/" */
      for(i=0;i<depth;i++){
	if(strncmp("../",linkbuf+(3*i),3))
	  break; /* not an annexed link */
      }
      if(strncmp(".git/annex/objects/",linkbuf+(3*depth),sizeof(".git/annex/objects/")-1))
	break; /* not an annexed link */

      /* skip over local/remote check if we are counting both */
      if(!(opt_countlocal&&opt_countremote)){
	struct stat s;
	int rslt;
	rslt=stat(path,&s);
	if(rslt==0 && opt_countlocal==0)
	  break; /* it is a local file and we aren't counting those */
	if(rslt!=0 && opt_countremote==0)
	  break; /* it is a remote file and we aren't counting those */
      }

      /* find the last '/' character */
      p=linkbuf+strlen(linkbuf);
      while( (p>linkbuf) && (*p)!='/' ) p--;

      if(regcomp(&regex,"[-]s([0-9]+)[-]",REG_EXTENDED)){
	fprintf(stderr,"%s: An error occured compiling the regex, this shouldn't be possible!\n",opt_progname);
	exit(RTRN_ERR_INTERNAL);
      }

      rslt=regexec(&regex,p,1,&regmatch,0);

      regfree(&regex);

      if(rslt || regmatch.rm_so<0)
	break; /* regex didn't match, not an annexed link?  Not an error? */

      p[regmatch.rm_so+2+strspn(p+regmatch.rm_so+2,"0123456789")]=0;
      mpz_set_str(size,p+regmatch.rm_so+2,10);
    }
  }while(0);

  if(cmdline || opt_outputall) printpath(size,path); /* output if this was a cmdline arg */

  return 0;
}

int dothedir(const char *path,mpz_t size, int output, unsigned int depth){
  DIR *d;
  struct dirent *de;
  mpz_t cursize;
  mpz_t tmpsize;
  char tmppath[PATH_MAX+1];
  size_t pathsize;

  /* try to open the dir */
  d=opendir(path);
  if(!d)
    return 2;

  /* calculate the pathsize and return an error if > PATH_MAX */
  pathsize=strlen(path);
  if(path[pathsize-1]!='/') pathsize+=1;
  if(pathsize>PATH_MAX)
    return 3;

  /* copy the path to tmppath and add a '/' if needed */
  strcpy(tmppath,path);
  if(path[pathsize-1]!='/') strcat(tmppath,"/");

  /* start with cursize of 0 */
  mpz_init_set_ui(cursize,0);
  mpz_init(tmpsize);

  /* for each directory entry... */
  while(de=readdir(d))
    /* if the entry is not "." or ".."... */
    if( strcmp(de->d_name,".") && strcmp(de->d_name,"..") ){
      /* if the resultant path will be larger than PATH_MAX return an error */
      if(strlen(de->d_name)+pathsize > PATH_MAX){
	mpz_clear(cursize); /* free cursize */
	mpz_clear(tmpsize); /* free tmpsize */
	return 3;
      }
      strcat(tmppath,de->d_name); /* add the entry to the path */
      if(!dothepath(tmppath,tmpsize,0,depth)) /* handle the new path */
	mpz_add(cursize,cursize,tmpsize); /* add to tally if successful */
      tmppath[pathsize]=0; /* remove the entry from the path */
    }

  closedir(d); /* close the directory */

  if(output || opt_outputall)
    printpath(cursize,path); /* output the result */

  mpz_swap(size,cursize); /* return the result */
  mpz_clear(cursize); /* free cursize */
  mpz_clear(tmpsize); /* free tmpsize */

  return 0;
}
