#include <stdio.h>
#include <string.h>
#include "include/chash.h"

int main() {
  int hash;
  char str[50];
  FILE *fp = fopen("cmdlist.dat", "r");

  fscanf(fp, "%s", str);
  while(!feof(fp)) {
    if(str[0] == '#') {
      hash = chash(&str[1]);
      printf("%d (%s)\n", hash, &str[1]);
    } else {
      hash = chash(str);
      printf("%d (%s)\n", hash, str);
    }
    fscanf(fp, "%s", str);
  }
}
