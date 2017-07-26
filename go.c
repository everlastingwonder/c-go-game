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
char **cmdParse(char*, char**);
Board *newGame(BoardSize, Board*);
Board *move(int, int, Space, Board*); //not done
void saveGame(char*, Board*);
Board *loadGame(char*, Board*);
void display(int, Board*);
void help();


// Menu function -- handles all user input and passes data to other functions
int main(int argc, char *argv[]) {
  // Welcome message
  printf("WELCOME TO CGG (C Go Game) %s\nBy Gus Wiedey\nType \'help\' for a list of commands.\n\n", VER_NUM);

  // Variable definitions
  int i, a, row, col, valid;
  int continueLoop = 1;
  char c, colChar, colMax;
  char *exitString = (char*)malloc(sizeof(char) * 100);
  char *cmd = (char*)malloc(sizeof(char) * CMD_LEN);
  char **args = (char**)malloc(sizeof(char*) * ARG_MAX);
  Board *board, *tmp;
  Space sp;
  BoardSize s;

  // malloc each element of **args
  for(i = 0; i < ARG_MAX; i++) {
    args[i] = (char*)malloc(sizeof(char) * ARG_LEN);
  }

  // Read & process user commands
  while(continueLoop) {
    printf("> ");
    fgets(cmd, CMD_LEN, stdin);
    cmdParse(cmd, args);

    if(!strcmp(args[0], "new")) {
      if(!strcmp(args[1], "beginner")) { s = beginner; }       // 9x9
      else if(!strcmp(args[1], "small")) { s = small; }        // 13x13
      else if(!strcmp(args[1], "standard")) { s = standard; }  // 19x19
      else {
        printf("ERROR: Invalid size argument \'%s\' - expected either \'beginner\', \'small\', or \'standard\'\n", args[1]);
        continue;
      }
      board = newGame(s, board);
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

      board = move(row, col, sp, board);
    }
    else if(!strcmp(args[0], "save")) {
      saveGame(args[1], board);
    }
    else if(!strcmp(args[0], "load")) {
      tmp = loadGame(args[1], board);
      if(tmp != NULL) {
        board = tmp;
      }
      else {
        printf("(Don't worry, the current game wasn't overwritten!)\n");
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
  printf("\nGoodbye!\n\n");
}


// Command parse function -- takes raw command string, splits it on spaces, and returns array containing split arguments
char **cmdParse(char *cmd, char *args[]) {
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

  // Add final terminating null char and return
  args[a][b] = '\0';
  return args;
}


// New game function -- starts a new game, defining a new Board structure of the proper size
Board *newGame(BoardSize s, Board *board) {
  // Variable definitions
  int i, j;

  // Define new instance of struct Board
  board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * s));
  board->dim = s;
  for(i = 0; i < board->dim; i++) {
    board->grid[i] = (Space*)malloc(sizeof(Space) * board->dim);
  }

  // Fill board with empty spaces and return
  for(i = 0; i < board->dim; i++) {
    for(j = 0; j < board->dim; j++) {
      board->grid[i][j] = empty;
    }
  }
  return board;
}


// Move function -- changes the state of one board space
Board *move(int row, int col, Space color, Board *board) {
  // This function is probably going to get a _lot_ bigger in the future, since I intend to handle most of the actual rules checking and processing here
  board->grid[row][col] = color;
  return board;
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
Board *loadGame(char *fname, Board *board) {
  // Variable definitions
  int i, j, s;
  char *rowData = (char*)malloc(sizeof(char) * 25);
  FILE *fp = fopen(fname, "r");
  BoardSize bsize;

  if(fp == NULL) {
    printf("ERROR: Could not open file \'%s\'\n", fname);
    return NULL;
  }

  // Scan size and make sure it is valid
  fscanf(fp, "%d", &s);
  switch(s) {
    case 9:
    case 13:
    case 19:
      bsize = s;
      board = newGame(bsize, board);
      break;
    default:
      printf("ERROR: Invalid board size in file \'%s\'\n", fname);
      return NULL;
      break;
  }

  // Scan board configuration
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
          printf("ERROR: Invalid board state data in file \'%s\'\n", fname);
          return NULL;
          break;
      }
    }
  }

  // Print success message and return loaded struct
  printf("Saved game successfully loaded from file \'%s\'.\n", fname);
  return board;
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
  printf("Sorry, nothing here yet!\n");
}
