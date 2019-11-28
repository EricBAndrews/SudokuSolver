#include "board.h"

// this file contains the definitions of the functions declared in board.h

struct Square initSquare(int val) {
  struct Square ret;
  ret.val = (uint8_t) val;
  ret.numOpts = 0;
  for (int i = 0; i < 9; ++i) {
    ret.opts[i] = 0;
  }
  return ret;
}

struct Board* initBoard() {
  struct Square* squares = malloc(sizeof(struct Square) * 81);
  struct Board* newBoard = malloc(sizeof(struct Board));
  newBoard->squares = squares;
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      newBoard->squares[(9 * i) + j] = initSquare(0);
    }
  }
  return newBoard;
}

void clearBoard(struct Board* toClear) {
  free(toClear->squares);
  free(toClear);
  return;
}
