#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#include <stdio.h>
#include <stdlib.h>

/* local headers */
#include <opts.h>
#include <common/returncodes.h>
#include <common/stub.h>

int main(int argc, char *argv[]){
  char **paths;

  paths=procopts(argc, argv);

  printf("Calling stub...\n");
  stub();
  printf("Done.\n");

  return RTRN_OK;
}
