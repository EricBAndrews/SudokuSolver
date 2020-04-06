#include "helper.h"
#include <stdlib.h>

// this file contains the definitions of the functions declared in helper.h

struct Board* parse(char* fName) {
  struct Board* ret = initBoard();
  FILE* boardFile = fopen(fName, "r");
  int i = 0;
  char ch = getc(boardFile);
  while (ch != EOF) {
    if (ch != '\n') {
      // printf("%i ", (int) ch - 48);
      ret->squares[i] = initSquare((int) ch - 48);
      if (ret->squares[i].val) {
        ret->squares[i].numOpts = 0;
        for (int j = 0; j < 9; ++j) {
          ret->squares[i].opts[j] = false;
        }
      }
      ++i;
    }
    ch = getc(boardFile);
  }
  return ret;
}

void printBoard(struct Board* toPrint) {
  printf("\n");
  for (int i = 0; i < 9; ++i) {
    if (i % 3 == 0 && i) {
      printf("---------------------\n");
    }
    for (int j = 0; j < 9; ++j) {
      if (j % 3 == 0 && j) {
        printf("| ");
      }
      printf("%i ", toPrint->squares[(9 * i) + j].val);
    }
    printf("\n");
  }
  printf("\n");
  return;
}
