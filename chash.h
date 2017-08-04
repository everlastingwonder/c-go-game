/*
* COMMAND HASH FUNCTION
* By Gus Wiedey
*/

#ifndef __C_HASH__
#define __C_HASH__

int chash(char* str) {
  int i, hash, shift, tmp;
  shift = 0;
  for(i = 0; i < strlen(str); i++) {
    tmp = str[i] << shift;
    hash = hash ^ tmp;
    shift = ((shift + 3) % 8);
  }
  return hash;
}

#endif
