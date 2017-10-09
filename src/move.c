#include "include/defs.h"

// Stupid macros (these do nothing whatsoever
// for code efficiency and serve no purpose
// except to make the code slightly easier to
// understand at a glance)
#define isEmpty(s) ((s == empty) ? 1 : 0)
#define isWhite(s) ((s == white) ? 1 : 0)
#define isBlack(s) ((s == black) ? 1 : 0)

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

  // Use chash() to determine what state
  // the given space should be set to
  switch(chash(state)) {
    case empty_case : sp = empty; _B;
    case white_case : sp = white; _B;
    case black_case : sp = black; _B;
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
