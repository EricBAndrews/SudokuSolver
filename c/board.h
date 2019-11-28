#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// this file contains the board struct and function declarations for
// all functions that operate directly on the board

struct Square {
  uint8_t val;
  uint8_t numOpts;
  uint8_t opts[9];
};

struct Board {
  struct Square* squares;
};

struct Square initSquare(int val);

struct Board* initBoard();

void clearBoard(struct Board* toClear);
