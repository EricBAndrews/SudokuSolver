#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

// this file contains the board struct and function declarations for
// all functions that operate directly on the board

struct Square {
  uint8_t val;
  uint8_t numOpts;
  bool opts[9]; // opts[i] represents i + 1. true if that option exists.
};

struct Board {
  struct Square* squares;
};

// returns a square with value val and options 1-9 excluding val
struct Square initSquare(int val);

// returns a board of all 0s and all options 1-9
struct Board* initBoard();

// deallocates memory for the given board
void clearBoard(struct Board* toClear);

// updates opts and numOpts of every square in row r by elimination
void updateRow(struct Board* b, int r);

// ditto
void updateCol(struct Board* b, int c);

// ditto
void updateBox(struct Board* b, int topLeft);

// calls updateRow, updateCol, and updateBox on each row, column, and box
void updateBoard(struct Board* b);

// repeatedly tries to solve the board by elimination; if that fails, starts recursing
void solve(struct Board* b);
