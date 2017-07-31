#include "defs.h"

void display(int printIndex, Board *board) {
  // Variable definitions
  int i, j;
  int row = 1;
  char col = 'A';

  // Print extra row containing column indices if printIndex is true
  if(printIndex) {
    printf("  ");
    for(i = 0; i < board->dim; i++) {
      printf(" %c", col);
      col++;
    }
    printf("\n\n");
  }

  // Loop to print out actual board state
  for(i = 0; i < board->dim; i++) {
    // Print row number at beginning of each row if printIndex is true
    if(printIndex) {
      printf("%02d ", row);
      row++;
    }

    // Print an actual row with pieces in it
    for(j = 0; j < board->dim; i++) {
      switch(board->grid[i][j]) {
        case empty:
        printf(" ");
        break;
        case white:
        printf("@");
        break;
        case black:
        printf("O");
        break;
      }

      if(j != (board->dim - 1)) {
        printf("-");
      }
    }
    printf("\n");

    // Pad non-numbered rows with extra spaces if row numbers are being printed so rows line up
    if(printIndex) {
      printf("   ");
    }

    // Print intermediate row unless previous row was the bottom one
    if(i != board->dim - 1) {
      for(j = 0; j < board->dim; j++) {
        printf("| ");
      }
    }
    printf("\n");
  }
}
