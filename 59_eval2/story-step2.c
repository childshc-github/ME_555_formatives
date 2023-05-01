#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  // make sure only given file w/ categories + words
  if (argc != 2) {
    fprintf(stderr, "Incorrect number of inputs given.\n");
    return EXIT_FAILURE;
  }

  // read from file
  char * file_name = argv[1];

  // create catarray_t
  catarray_t * answer = readCW(file_name);

  // print w/ printWords
  printWords(answer);

  // free struct
  free_catarry(answer);

  return 0;
}
