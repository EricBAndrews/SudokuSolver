#include "helper.h"

// this is the main file, it runs everything

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("please give a valid filename as an argument\n");
  }

  struct Board* test = parse("test");
  printBoard(test);
  return 0;
}
