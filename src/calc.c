#include <stdio.h>
#include "include/chash.h"

int main(int argc, char **argv) {
  if(argc == 1) {
    printf("Enter a filename!\n");
    return 4;
  } else {
    hashdef(argv[1]);
    return 0;
  }
}
