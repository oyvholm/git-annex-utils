#include <stdio.h>
#include <stdlib.h>

#include <common/stub.h>

void foo(char *);

int main(int argc, char *argv[]){
  printf("Calling stub...\n");
  stub();
  printf("Done.\n");
  return 0;
}
