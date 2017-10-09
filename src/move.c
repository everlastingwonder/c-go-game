#include "include/defs.h"

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

// UPDATE ALGORITHM PSEUDOCODE //
/*
*  WHEN a stone is placed,
*    FOR EACH contiguous group of like-colored stones,
*      IF THAT group has no adjacent empty spaces AND does not contain the most recently placed stone,
*        THEN THAT group is removed,
*        ELSE THAT group stays;
*    IF the group containing the most recently placed stone has no adjacent empty spaces,
*      THEN THAT group is removed,
*      ELSE THAT group stays;
*  END
*/

void update(int row, int col, Board *board) {
  // Variable definitions
  int i, j;
  Space moveColor = board[row][col];

  // Check each space adjacent to most recent move
}
