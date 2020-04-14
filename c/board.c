// #include "board.h"
#include "helper.h"
#include<unistd.h>

// this file contains the definitions of the functions declared in board.h

struct Square initSquare(int val) {
  struct Square ret;
  ret.val = (uint8_t) val;
  ret.numOpts = (val == 0) ? 9 : 0; // 0 options represents fixed number
  for (int i = 0; i < 9; ++i) {
    ret.opts[i] = (i + 1 == val) ? false : true;
  }
  return ret;
}

struct Board* initBoard() {
  struct Square* squares = malloc(sizeof(struct Square) * 81);
  struct Board* newBoard = malloc(sizeof(struct Board));
  newBoard->squares = squares;
  for (int i = 0; i < 81; ++i) {
    newBoard->squares[i] = initSquare(0);
  }
  return newBoard;
}

struct Square copySquare(struct Square toCopy) {
  struct Square ret;
  ret.val = toCopy.val;
  ret.numOpts = toCopy.numOpts;
  for (int i = 0; i < 9; ++i) {
    ret.opts[i] = toCopy.opts[i];
  }
  return ret;
}

struct Board* copyBoard(struct Board* toCopy) {
  struct Board* ret = malloc(sizeof(struct Board));
  ret->squares = malloc(sizeof(struct Square) * 81);
  for (int i = 0; i < 81; ++i) {
    ret->squares[i] = copySquare(toCopy->squares[i]);
  }
  return ret;
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
      if (cur->numOpts) {
        val = inRow[j];
        if (cur->opts[val - 1]) {
          cur->numOpts -= 1;
        }
        cur->opts[val - 1] = false;
      }
    }
  }

  return;
}

void updateCol(struct Board* b, int c) {
  uint8_t inCol[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  int i = 0;
  uint8_t val;

  // generate list of numbers in col
  for (int r = 0; r < 9; ++r) {
    val = b->squares[r * 9 + c].val;
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
          cur->numOpts -= 1;
        }
        cur->opts[val - 1] = false;
      }
    }
  }
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
            cur->numOpts -= 1;
          }
          cur->opts[val - 1] = false;
        }
      }
    }
  }
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
    }
  }
  return;
}

int findMin(struct Board* b) {
  int min = -1;
  int minOpts = 10;
  for (int i = 0; i < 81; ++i) {
    if (b->squares[i].numOpts && b->squares[i].numOpts < minOpts) {
      min = i;
      minOpts = b->squares[i].numOpts;
    }
  }
  if (min == -1) {
    printf("something has gone terribly wrong, no min square!\n");
  }
  return min;
}

void solve(struct Board* b) {
  // change values (simplistic, no recursion yet)
  // TODO: recursion if needed
  bool solved = false;
  bool updated;
  while (!solved) {
    printBoard(b); //TESTING
    updateBoard(b);
    sleep(1); //TESTING

    // keep track of board state for looping and recursing
    solved = true;
    updated = false;

    // loop through each square; update its value if possible
    for (int i = 0; i < 81; ++i) {
      struct Square* cur = &(b->squares[i]);
      if (cur->numOpts == 1) {
        updated = true;
        cur->numOpts = 0;
        for (int j = 0; j < 9; ++j) {
          if (cur->opts[j]) {
            cur->val = j + 1;
            break;
          }
        }
      }
      // if the square has options, board is not solved
      else if (cur->numOpts) {
        solved = false;
      }
    }

    // if board not solved and not updated, time to recurse
    if (!solved && !updated) {
      int minSquare = findMin(b);
      printf("min square: %i\n", minSquare);
    }
  }
}
