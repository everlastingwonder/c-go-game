/*
* CGG (C Go Game)
* By Gus Wiedey
* Version 0.1.0
*/

/**********************
*  PREPROCESSOR CRAP  *
**********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VER_NUM "0.1.0"
#define CMD_LEN 50
#define ARG_MAX 5
#define ARG_LEN 10

/*********************
*  TYPE DEFINITIONS  *
*********************/
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

/**********************
*      FUNCTIONS      *
**********************/
int cmdParse(char*, char**);
void move(int, int, Space, Board*);
void saveGame(char*, Board*);
int loadGame(char*, Board*);
void display(int, Board*);
void help();


// Menu function -- handles all user input and passes data to other functions
int main(int argc, char *argv[]) {
  // Welcome message
  printf("WELCOME TO CGG (C Go Game) %s\nBy Gus Wiedey\nType \'help\' for a list of commands.\n\n", VER_NUM);

  // Variable definitions
  int a, i, j, row, col, valid, argCount, loadResult;
  int continueLoop = 1;
  char c, colChar, colMax;
  char cmd[CMD_LEN], exitString[60];
  char **args = (char**)malloc(sizeof(char*) * ARG_MAX);
  Board *board;
  Space sp;

  // malloc each element of **args
  for(i = 0; i < ARG_MAX; i++) {
    args[i] = (char*)malloc(sizeof(char) * ARG_LEN);
  }

  // Read & process user commands
  while(continueLoop) {
    printf("> ");
    fgets(cmd, CMD_LEN, stdin);
    argCount = cmdParse(cmd, args);

    if(!strcmp(args[0], "init")) {
      // Allocate memory for a new board of the correct size
      if(!strcmp(args[1], "beginner")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 9));
        board->dim = beginner;
      }
      else if(!strcmp(args[1], "small")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 13));
        board->dim = small;
      }
      else if(!strcmp(args[1], "standard")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 19));
        board->dim = standard;
      }
      else {
        printf("ERROR: Invalid size argument \'%s\' - expected either \'beginner\', \'small\', or \'standard\'\n", args[1]);
        continue;
      }

      // Allocate memory for grid rows and fill grid with empty spaces
      for(i = 0; i < board->dim; i++) {
        board->grid[i] = (Space*)malloc(sizeof(Space) * board->dim);
        for(j = 0; j < board->dim; j++) {
          board->grid[i][j] = empty;
        }
      }

      printf("New game created (board size %dx%d)\n", board->dim, board->dim);
    }
    else if(!strcmp(args[0], "show")) {
      if(!strcmp(args[1], "noindex")) {
        display(0, board);
      }
      else {
        display(1, board);
      }
    }
    else if(!strcmp(args[0], "move")) {
      valid = 1;

      for(i = 0; i < strlen(args[1]); i++) {
        if(!isdigit(args[1][i])) {
          printf("ERROR: Invalid row argument \'%s\' - expected integer\n", args[1]);
          valid = 0;
        }
      }
      if(!valid) {
        continue;
      }

      sscanf(args[1], "%d", &row);
      if((row < 1) || (row > board->dim)) {
        printf("ERROR: Invalid row argument \'%s\' - expected value between 1 and %d\n", args[1], board->dim);
        continue;
      }

      row--;
      if(strlen(args[2]) != 1) {
        printf("ERROR: Invalid column argument \'%s\' - expected single character\n", args[2]);
        continue;
      }

      colChar = tolower(args[2][0]);
      colMax = board->dim + 96;
      if((colChar < 'a') || (colChar > colMax)) {
        printf("ERROR: Invalid column argument \'%c\' - expected value between \'a\' and \'%c\'\n", colChar, colMax);
        continue;
      }

      col = colChar - 97;
      if(!strcmp(args[3], "white")) {
        sp = white;
      }
      else if(!strcmp(args[3], "black")) {
        sp = black;
      }
      else if(!strcmp(args[3], "empty")) {
        sp = empty;
      }
      else {
        printf("ERROR: Invalid color argument \'%s\' - expected either \'black\', \'white\', or \'empty\'\n", args[3]);
        continue;
      }

      move(row, col, sp, board);
    }
    else if(!strcmp(args[0], "save")) {
      saveGame(args[1], board);
    }
    else if(!strcmp(args[0], "load")) {
      loadResult = loadGame(args[1], board);
      switch(loadResult) {
        case 0:
        printf("Saved game successfully loaded from file \'%s\'.\n", args[1]);
        break;
        case 1:
        printf("ERROR: Could not open file \'%s\'\n", args[1]);
        break;
        case 2:
        printf("ERROR: Invalid board size parameter in file \'%s\'\n", args[1]);
        break;
        case 3:
        printf("ERROR: Invalid board state data in file \'%s\'\n", args[1]);
        break;
      }
    }
    else if(!strcmp(args[0], "help")) {
      help();
    }
    else if(!strcmp(args[0], "quit")) {
      // set continueLoop to false so that loop ends
      continueLoop = 0;
    }
    else if(!strcmp(args[0], "")) {
      // extra condition to prevent program from printing error message if user simply hits enter with no input
      continue;
    }
    else {
      // error message for invalid input
      printf("ERROR: Unknown command \'%s\'. (Type \'help\' for a list of commands)\n", args[0]);
    }
  }

  // Ask user if they want to save before quitting (and then quit)
  strcpy(exitString, "Do you want to save your game before quitting? (y/n): ");
  do {
    printf("%s", exitString);
    c = getc(stdin);
    switch(tolower(c)) {
      case 'y':
      printf("\nWhere do you want to save your game?\nFilename: ");
      fgets(cmd, CMD_LEN, stdin);
      cmdParse(cmd, args);
      saveGame(args[0], board);
      printf("Game saved to file %s\n", args[0]);
      continueLoop = 0;
      break;
      case 'n':
      printf("\n");
      continueLoop = 0;
      break;
      default:
      strcpy(exitString, "Please enter either y or n: ");
      continueLoop = 1;
      break;
    }
  } while(continueLoop);
  printf("Goodbye!\n\n");
}


// Command parse function -- takes raw command string, splits it on spaces, and returns array containing split arguments
int cmdParse(char *cmd, char *args[]) {
  // Variable definitions
  int i = 0; // current index in string cmd
  int a = 0; // current index in array args
  int b = 0; // current index in string args[a]

  // While loop to iterate over the raw string and split it into arguments
  while((cmd[i] != '\0') && (cmd[i] != '\n') && (i < CMD_LEN)) {
    if(cmd[i] == ' ') {
      args[a][b] = '\0';
      a++;
      b = 0;
    }
    else {
      args[a][b] = cmd[i];
      b++;
    }
    i++;
  }

  // Add final terminating null char and return number of arguments
  args[a][b] = '\0';
  return (a + 1);
}


// Move function -- changes the state of one board space
void move(int row, int col, Space color, Board *board) {
  // This function is going to get WAY bigger in the future, since I intend to handle most of the actual rules checking and processing here
  board->grid[row][col] = color;
}


// Save function -- saves the current board state to a file
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


// Load function -- loads a saved board state from a file
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


// Show board function -- prints a representation of the current board state to stdout
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


// Help function -- prints help message
void help() {
  printf("Valid commands: init, show, move, save, load, help, quit\n");
}
