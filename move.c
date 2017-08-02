#include "defs.h"

int move(char *r, char *c, char *state, Board *board) {
  // Variable definitions
  int row, col;
  char tmp;
  Space sp;

  // Do as much error checking as possible up front
  // so everything else is neater and more efficient
  if(r[0] == '!') {
    if(sscanf(c, "%d%c", &row, &tmp) != 2) { return -1; }
  } else {
    if(sscanf(r, "%d", &row) != 1) { return 1; }
    if(!isalpha(c[0])) { return 2; }
  }

  // Figure out what state the given space should be based on
  // the first character of *state (rather than the whole string),
  // because this allows us to use a nice neat switch statement
  // instead of an ugly chain of ifs and else-ifs
  switch(state[0]) {
    case 'e' : sp = empty; _B;
    case 'w' : sp = white; _B;
    case 'b' : sp = black; _B;
    default : return 3; _B;
  }

  // Translate column char into integer and check whether
  // row and col are valid (i.e. between 0 and board->dim)
  if(row > board->dim) { return 4; }
  row--;
  col = (tolower(c[0]) - 97);
  if(col >= board->dim) { return 5; }

  // Change the actual space in board->grid and return 0 for success
  board->grid[row][col] = sp;
  return 0;
}
