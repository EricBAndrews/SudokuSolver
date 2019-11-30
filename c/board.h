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

// returns a square with value val and options 1-9 excluding val
struct Square initSquare(int val);

// returns a board of all 0s and all options 1-9
struct Board* initBoard();

void clearBoard(struct Board* toClear);

void updateRow(struct Board* b, int r);

void updateCol(struct Board* b, int c);

void updateBox(struct Board* b, int topLeft);

void updateBoard(struct Board* b);
