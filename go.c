/*
* CGG (C Go Game)
* By Gus Wiedey
* Version 0.2
*/

#include "defs.h"
#include "chash.h"
#include "hashes.h"

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

  // Create struct pointer to represent gameboard and allocate memory for board (and each row of board->grid)
  Board *board = (Board*)malloc(sizeof(Board) + (sizeof(Space*) * DIM_MAX));
  for(i = 0; i < DIM_MAX; i++) {
    board->grid[i] = (Space*)malloc(sizeof(Space) * DIM_MAX);
  }

  // Create (and allocate memory for) array of strings to hold processed user input from cmdParse
  char **args = (char**)malloc(sizeof(char*) * ARG_MAX);
  for(i = 0; i < ARG_MAX; i++) {
    args[i] = (char*)malloc(sizeof(char) * ARG_LEN);
  }

  // Read & process user commands
  while(loop) {
    printf("> ");
    fgets(cmd, CMD_LEN, stdin);
    argCount = cmdParse(cmd, args);
    if(!strcmp(args[0], "")) {
      // Extra condition to prevent program from printing an error message if user simply hits enter
      // without typing anything. (I left this as a standalone condition rather than putting it in the
      // switch statement because I'm not sure how chash() will behave with an empty string as input)
      continue;
    }

    switch(chash(args[0])) {
      case init_h:
      // Set board->dim to the correct size
      exitVal = 0;
      switch(chash(args[1])) {
        case tiny_h : board->dim = tiny; _B;
        case small_h : board->dim = small; _B;
        case standard_h : board->dim = standard; _B;
        default : exitVal = 1; _B;
      }
      // Fill grid with empty spaces (assuming user input was valid)
      if(exitVal) {
        printf("ERROR: Invalid size argument \'%s\' - expected either \'tiny\', \'small\', or \'standard\'\n", args[1]);
      } else {
        for(i = 0; i < board->dim; i++) {
            for(j = 0; j < board->dim; j++) {
              board->grid[i][j] = empty;
            }
          }
        printf("New game created (board size %dx%d)\n", board->dim, board->dim);
      }
      break;
      /********************************/
      case move_h:
      switch(argCount) {
          case 3 : exitVal = move("!", args[1], args[2], board); _B;
          case 4 : exitVal = move(args[1], args[2], args[3], board); _B;
          default : exitVal = -99; _B;
        }
      switch(exitVal) {
          case 0 : _B; // An exit value of 0 indicates that move() completed successfully; this case is just here as a placeholder
          case -99: printf("ERROR: Invalid number of arguments (expected either 3 or 4; received %d)", argCount); _B;
          case -1 : printf("uh oh something is borken\n"); _B;
          case 1 : printf("uh oh something is borken\n"); _B;
          case 2 : printf("uh oh something is borken\n"); _B;
          case 3 : printf("uh oh something is borken\n"); _B;
          case 4 : printf("uh oh something is borken\n"); _B;
          case 5 : printf("uh oh something is borken\n"); _B;
        }
      break;
      /********************************/
      case load_h:
      exitVal = loadGame(args[1], board);
      switch(exitVal) {
          case 0 : printf("\nGame data successfully loaded.\n"); _B;
          case 1 : printf("\nERROR: Failed to open file.\n"); _B;
          case 2 : printf("\nERROR: Invalid board size parameter.\n"); _B;
          case 3 : printf("\nERROR: Invalid board state data.'\n"); _B;
        }
      break;
      /********************************/
      // Print graphical representation of current board state to stdout
      case show_h : display(board); _B;
      // Save current board state to file
      case save_h : saveGame(args[1], board); _B;
      // Print help message
      case help_h : help(); _B;
      // Set loop to false so the while loop will exit after the current iteration
      case quit_h : loop = 0; _B;
      // Error message for invalid input
      default : printf("ERROR: Unknown command \'%s\'. (Type \'help\' for a list of commands)\n", args[0]); _B;
    }
  }

  // Ask user if they want to save before quitting (and then quit)
  strcpy(exitString, "Do you want to save your game before quitting? (y/n): ");
  do {
    printf("%s", exitString);
    c = fgetc(stdin);
    if(c == '\n') { c = fgetc(stdin); }
    switch(tolower(c)) {
      case 'y':
      printf("\nEnter a name for your save file: ");
      fgets(cmd, CMD_LEN, stdin); // No, this isn't a typo. Two fgets() calls are needed here; the first one clears out any leftover
      fgets(cmd, CMD_LEN, stdin); // input in the stdin buffer, and the second one reads the string that we're actually looking for.
      for(i = 0; i < CMD_LEN; i++) {
        if(cmd[i] == '\n') {
          cmd[i] = '\0';
          break;
        }
      }
      saveGame(cmd, board);
      // break intentionally omitted here
      case 'n':
      loop = 0;
      printf("\n");
      break;
      /****************/
      default:
      strcpy(exitString, "Please enter either y or n: ");
      loop = 1;
      break;
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
