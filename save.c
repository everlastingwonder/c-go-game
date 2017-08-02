#include "defs.h"

void saveGame(char *fname, Board *board) {
  // Variable definitions
  int i, j;
  FILE *fp = fopen(fname, "w");

  // Print board size on first line
  fprintf(fp, "%d\n", board->dim);

  // Print grid
  for(i = 0; i < board->dim; i++) {
    for(j = 0; j < board->dim; j++) {
      fprintf(fp, "%d", board->grid[i][j]);
    }
    fprintf(fp, "\n");
  }

  // Close file and print "game saved" message
  printf("Game saved to file \'%s\'.\n", fname);
  fclose(fp);
}


int loadGame(char *fname, Board *board) {
  // Variable definitions
  int i, j, s;
  char rowData[25];
  FILE *fp = fopen(fname, "r");

  printf("Loading saved game from file %s ", fname);

  // Error message if file fails to open
  if(fp == NULL) {
    return 1;
  }
  printf(". ");

  // Scan size, make sure it's valid, and set board->dim appropriately
  fscanf(fp, "%d", &s);
  switch(s) {
    case 9 : board->dim = tiny; _B;
    case 13 : board->dim = small; _B;
    case 19 : board->dim = standard; _B;
    default : return 2; _B;
  }

  printf(". ");

  // Scan board configuration from file
  for(i = 0; i < board->dim; i++) {
    fscanf(fp, "%s", rowData);
    for(j = 0; j < board->dim; j++) {
      switch(rowData[j]) {
        case '0' : board->grid[i][j] = empty; _B;
        case '1' : board->grid[i][j] = white; _B;
        case '2' : board->grid[i][j] = black; _B;
        default : return 3; _B;
      }
    }
  }
  printf(". ");

  return 0;
}
