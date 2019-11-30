#include "board.h"

// this file contains the definitions of the functions declared in board.h

struct Square initSquare(int val) {
  struct Square ret;
  ret.val = (uint8_t) val;
  ret.numOpts = 0;
  int curOpt = 1;
  for (int i = 0; i < 9; ++i) {
    if (curOpt == val) {
      ++curOpt;
    }
    else {
      ret.opts[i] = curOpt;
      ++curOpt;
    }
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

void updateRow(struct Board* b, int r) {
  uint8_t inRow[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;
  uint8_t val;

  // generate list of numbers in row
  for (int c = 0; c < 9; ++c) {
    val = b->squares[r * 9 + c].val;
    printf("%i\n", val);
    if (val) {
      inRow[i] = val;
      ++i;
    }
  }

  // update options in row--for each character in row, remove from options
  // of space on board
  for (int c = 0; c < i; ++c) {
    val = inRow[c];
    struct Square cur = b->squares[r * 9 + c];
    cur.opts[val - 1] = 0;
    // TODO: TEST!
  }
  return;
}

void updateCol(struct Board* b, int c) {
  return;
}

void updateBox(struct Board* b, int topLeft) {
  return;
}

void updateBoard(struct Board* b) {
  return;
}
