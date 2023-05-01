#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  // make sure given both files
  if (argc != 3) {
    fprintf(stderr, "Incorrect number of inputs given.\n");
    return EXIT_FAILURE;
  }

  // get CW file name
  char * file_CW = argv[1];

  // get story template file name
  char * file_story = argv[2];

  // get catarray
  catarray_t * answer = readCW(file_CW);

  // print story
  print_story(file_story, answer);

  // free catarray
  free_catarry(answer);

  return 0;
}
