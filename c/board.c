#include "board.h"

// this file contains the definitions of the functions declared in board.h

struct Board* initBoard() {
  struct Square* squares = malloc(sizeof(struct Square) * 81);
  struct Board* newBoard = malloc(sizeof(struct Board));
  newBoard->squares = squares;
  return newBoard;
}

void clearBoard(struct Board* toClear) {
  free(toClear->squares);
  free(toClear);
  return;
}
