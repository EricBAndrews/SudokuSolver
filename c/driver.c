#include "helper.h"

// this is the main file, it runs everything

int main(int argc, char** argv) {
  /* if (argc != 2) { */
  /*   printf("please give a valid filename as an argument\n"); */
  /* } */

  struct Board* test = parse("board0.txt");
  printf("original board:\n");
  struct Board* testCopy = copyBoard(test);
  test->squares[0].val = 9;
  printBoard(test);
  printf("\n\nnew board: \n");
  printBoard(testCopy);
  //updateBoard(test);
  // solve(test);
  
  //printBoard(test);
  return 0;
}
