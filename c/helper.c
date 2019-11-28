#include "helper.h"
#include <stdlib.h>

// this file contains the definitions of the functions declared in helper.h

struct Board* parse(char* fName) {
  struct Board* ret = initBoard();
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
