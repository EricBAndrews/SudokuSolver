#include "board.h"

// this file contains the definitions of the functions declared in board.h

struct Square initSquare(int val) {
  struct Square ret;
  ret.val = (uint8_t) val;
  ret.numOpts = (val == 0) ? 9 : 0; // 0 options represents fixed number
  // int curOpt = 1;
  for (int i = 0; i < 9; ++i) {
    ret.opts[i] = (i + 1 == val) ? false : true;
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
    // printf("%i\n", val);
    if (val) {
      inRow[i] = val;
      ++i;
    }
  }

  // update options in row--for each character in row, remove from options
  // of space on board
  for (int c = 0; c < 9; ++c) {
    struct Square* cur = &(b->squares[r * 9 + c]);
    // for each value in inRow, remove from cur's options
    for (int j = 0; j < i; ++j) {
      // printf("nOpts: %i, cur: [%i,%i]\n", cur->numOpts, r, c);
      if (cur->numOpts) {
        val = inRow[j];
        if (cur->opts[val - 1]) {
          // printf("has option %i\n", val);
          cur->numOpts -= 1;
          // printf("has %i opts\n", cur->numOpts);
        }
        cur->opts[val - 1] = false;
      }
    }
  }

  // testing
  /*
  for (int i = 0; i < 9; ++i) {
    struct Square cur = b->squares[r * 9 + i];
    printf("col %i has the following options:", i);
    for (int j = 0; j < 9; ++j) {
      if (cur.opts[j]) {
        printf(" %i", j + 1);
      }
    }
    printf("\n and it has %i options\n", cur.numOpts);
  }
  */
  return;
}

void updateCol(struct Board* b, int c) {
  uint8_t inCol[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;
  uint8_t val;

  // generate list of numbers in col
  for (int r = 0; r < 9; ++r) {
    val = b->squares[r * 9 + c].val;
    // printf("%i\n", val);
    if (val) {
      inCol[i] = val;
      ++i;
    }
  }

  // update options in row--for each character in col, remove from options
  // of space on board
  for (int r = 0; r < 9; ++r) {
    struct Square* cur = &(b->squares[r * 9 + c]);
    for (int j = 0; j < i; ++j) {
      if (cur->numOpts) {
        val = inCol[j];
        if (cur->opts[val - 1]) {
          //printf("has option %i\n", val);
          cur->numOpts -= 1;
          //printf("has %i opts\n", cur->numOpts);
        }
        cur->opts[val - 1] = false;
      }
    }
  }

  // testing
  /*
  for (int r = 0; r < 9; ++r) {
    struct Square cur = b->squares[r * 9 + c];
    printf("row %i has the following options:", r);
    for (int j = 0; j < 9; ++j) {
      if (cur.opts[j]) {
        printf(" %i", j + 1);
      }
    }
    printf("\n and it has %i options\n", cur.numOpts);
  }
  */
  return;
}

void updateBox(struct Board* b, int topLeft) {
  // takes in top left corner's index
  uint8_t inBox[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;
  uint8_t val;
  
  // helper variables; describe top left corner in r/c notation
  int cornerR = topLeft / 9;
  int cornerC = topLeft % 9;

  // generate list of numbers in box
  for (int r = cornerR; r < cornerR + 3; ++r) {
    for (int c = cornerC; c < cornerC + 3; ++c) {
      val = b->squares[r * 9 + c].val;
      // printf("%i\n", val);
      if (val) {
        inBox[i] = val;
        ++i;
      }
    }
  }

  // update options in box--for each character in box, remove from options
  // of space on board
  for (int r = cornerR; r < cornerR + 3; ++r) {
    for (int c = cornerC; c < cornerC + 3; ++c) {
      struct Square* cur = &(b->squares[r * 9 + c]);
      for (int j = 0; j < i; ++j) {
        if (cur->numOpts) {
          val = inBox[j];
          if (cur->opts[val - 1]) {
            //printf("has option %i\n", val);
            cur->numOpts -= 1;
            //printf("has %i opts\n", cur->numOpts);
          }
          cur->opts[val - 1] = false;
        }
      }
    }
  }

  // testing
  /*
  for (int r = cornerR; r < cornerR + 3; ++r) {
    for (int c = cornerC; c < cornerC + 3; ++c) {
      struct Square cur = b->squares[r * 9 + c];
      printf("box [%i, %i] has the following options:", r, c);
      for (int j = 0; j < 9; ++j) {
        if (cur.opts[j]) {
          printf(" %i", j + 1);
        }
      }
      printf("\n and it has %i options\n", cur.numOpts);
    }
  }
  */
  return;
}

void updateBoard(struct Board* b) {
  // update by rows
  for (int i = 0; i < 9; ++i) {
    updateRow(b, i);
  }
  
  // update by columns
  for (int i = 0; i < 9; ++i) {
    updateCol(b, i);
  }

  // update by boxes
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      updateBox(b, i * 27 + j * 3); // math to generate topLeft
      //printf ("%i\n", i * 27 + j * 3);
    }
  }

  // change values (simplistic, no recursion yet)
  // TODO: recursion if needed
  for (int r = 0; r < 9; ++r) {
    for (int c = 0; c < 9; ++c) {
      struct Square* cur = &(b->squares[r * 9 + c]);
      if (cur->numOpts == 1) {
        cur->numOpts = 0;
        for (int i = 0; i < 9; ++i) {
          if (cur->opts[i]) {
            cur->val = i + 1;
            break;
          }
        }
      }
    }
  }
  return;
}
