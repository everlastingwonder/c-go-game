#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VER_NUM "v0.1.0"
#define CMD_LEN 50
#define ARG_MAX 5
#define ARG_LEN 10

enum SPACE {
  empty = 0,
  white = 1,
  black = 2
};
typedef enum SPACE Space;

enum BOARDSIZE {
  beginner = 9,
  small = 13,
  standard = 19
};
typedef enum BOARDSIZE BoardSize;

struct BOARD {
  BoardSize dim;
  Space *grid[];
};
typedef struct BOARD Board;
