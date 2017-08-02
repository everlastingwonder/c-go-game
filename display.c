#include "defs.h"

void display(Board *board) {
  // Variable definitions
  int i, j;
  int row = 1;
  char col = 'A';

  // Print extra row containing column indices
  printf("\n ");
  for(i = 0; i < board->dim; i++) {
    printf("  %c", col);
    col++;
  }
  printf("\n");

  // Loop to print out actual board state
  for(i = 0; i < board->dim; i++) {
    // Print row number at beginning of each row
    printf("%02d ", row);
    row++;

    // Print an actual row with pieces in it
    for(j = 0; j < board->dim; j++) {
      switch(board->grid[i][j]) {
        case empty : printf(" "); _B;
        case white : printf("@"); _B;
        case black : printf("O"); _B;
      }

      if(j != (board->dim - 1)) {
        printf("--");
      }
    }
    printf("\n");

    // Print intermediate row unless previous row was the bottom one
    if(i != board->dim - 1) {
      printf("   ");
      for(j = 0; j < board->dim; j++) {
        printf("|  ");
      }
    }
    printf("\n");
  }
}
