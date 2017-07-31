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
    printf("\n");
  }

  // Close file and print "game saved" message
  printf("Game saved to file \'%s\'.\n", fname);
  fclose(fp);
}


int loadGame(char *fname, Board *board) {
  // Variable definitions
  int i, j, s;
  char *rowData = (char*)malloc(sizeof(char) * 25);
  FILE *fp = fopen(fname, "r");

  printf("Warning: Current game will be overwritten!\n");
  printf("Loading game from file");

  // Error message if file fails to open
  if(fp == NULL) {
    return 1;
  }
  printf(" .");

  // Scan size, make sure it's valid, and malloc() board struct
  fscanf(fp, "%d", &s);
  switch(s) {
    case 9:
    board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 9));
    board->dim = beginner;
    break;
    case 13:
    board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 13));
    board->dim = small;
    break;
    case 19:
    board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 19));
    board->dim = standard;
    break;
    default:
    return 2;
    break;
  }

  // malloc() each Space* pointer in board->grid
  for(i = 0; i < board->dim; i++) {
    board->grid[i] = (Space*)malloc(sizeof(Space) * board->dim);
  }
  printf(" .");

  // Scan board configuration from file
  for(i = 0; i < board->dim; i++) {
    fgets(rowData, 25, fp);
    for(j = 0; j < board->dim; j++) {
      switch(rowData[j]) {
        case '0':
        board->grid[i][j] = empty;
        break;
        case '1':
        board->grid[i][j] = white;
        break;
        case '2':
        board->grid[i][j] = black;
        break;
        default:
        return 3;
        break;
      }
    }
  }
  printf(" .\n");

  return 0;
}
