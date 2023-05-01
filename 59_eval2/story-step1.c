#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  // make sure get input
  if (argc != 2) {
    fprintf(stderr, "Incorrect number of inputs given.\n");
    return EXIT_FAILURE;
  }

  // format check
  format_checker(argv[1]);

  // print story
  print_story(argv[1], NULL);

  return 0;
}
