/*
* CGG (C Go Game)
* By Gus Wiedey
* Version 0.1.1
*/

#include "defs.h"

int cmdParse(char*, char**);
int move(char*, char*, char*, Board*);
void saveGame(char*, Board*);
int loadGame(char*, Board*);
void display(Board*);
void help();

int main(int argc, char *argv[]) {
  // Welcome message
  printf("WELCOME TO CGG (C Go Game) %s\nBy Gus Wiedey\nType \'help\' for a list of commands.\n\n", VER_NUM);

  // Variable definitions
  int a, i, j, valid, argCount, exitVal;
  int loop = 1;
  char c, colChar, colMax;
  char cmd[CMD_LEN], exitString[60];
  char **args = (char**)malloc(sizeof(char*) * ARG_MAX);
  Board *board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * DIM_MAX))

  // malloc each element of **args
  for(i = 0; i < ARG_MAX; i++) {
    args[i] = (char*)malloc(sizeof(char) * ARG_LEN);
  }

  // Read & process user commands
  while(loop) {
    printf("> ");
    fgets(cmd, CMD_LEN, stdin);
    argCount = cmdParse(cmd, args);

    if(!strcmp(args[0], "init")) {
      // Allocate memory for a new board of the correct size
      if(!strcmp(args[1], "tiny")) {
        board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * 9));
        board->dim = tiny;
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
        printf("ERROR: Invalid size argument \'%s\' - expected either \'tiny\', \'small\', or \'standard\'\n", args[1]);
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
        display(board);
    }
    else if(!strcmp(args[0], "move")) {
      switch(argCount) {
        case 3 : exitVal = move("!", args[1], args[2], board); _B;
        case 4 : exitVal = move(args[1], args[2], args[3], board); _B;
        default : printf("ERROR: Invalid number of arguments (expected either 3 or 4; received %d)", argCount); _B;
      }
      switch(exitVal) {
        case 0 : _B; // An exit value of 0 indicates that move() completed successfully; this case is just here as a placeholder
        case -1 : printf("uh oh something is borken\n"); _B;
        case 1 : printf("uh oh something is borken\n"); _B;
        case 2 : printf("uh oh something is borken\n"); _B;
        case 3 : printf("uh oh something is borken\n"); _B;
        case 4 : printf("uh oh something is borken\n"); _B;
        case 5 : printf("uh oh something is borken\n"); _B;
      }
    }
    else if(!strcmp(args[0], "save")) {
      saveGame(args[1], board);
    }
    else if(!strcmp(args[0], "load")) {
      exitVal = loadGame(args[1], board);
      switch(exitVal) {
        case 0 : printf("\nSaved game successfully loaded from file \'%s\'.\n", args[1]); _B;
        case 1 : printf("\nERROR: Could not open file \'%s\'\n", args[1]); _B;
        case 2 : printf("\nERROR: Invalid board size parameter in file \'%s\'\n", args[1]); _B;
        case 3 : printf("\nERROR: Invalid board state data in file \'%s\'\n", args[1]); _B;
      }
    }
    else if(!strcmp(args[0], "help")) {
      help();
    }
    else if(!strcmp(args[0], "quit")) {
      // set loop to false so that loop ends
      loop = 0;
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
  loop = 0;
  do {
    printf("%s", exitString);
    c = getc(stdin);
    switch(tolower(c)) {
      case 'y':
      printf("\nFile to save game to: ");
      fgets(cmd, CMD_LEN, stdin);
      cmdParse(cmd, args);
      saveGame(args[0], board);
      printf("Game saved to file %s\n", args[0]); _B;
      /****************/
      case 'n':
      printf("\n"); _B;
      /****************/
      default:
      strcpy(exitString, "Please enter either y or n: ");
      loop = 1; _B;
    }
  } while(loop);
  printf("Goodbye!\n\n");
}

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
