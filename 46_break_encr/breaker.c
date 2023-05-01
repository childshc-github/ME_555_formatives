#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//input : name of file
int crack(FILE * f) {
  // initialize vars
  int key = 0;
  int trackArray[26] = {0};
  int c;
  int current_max = 0;

  // count chars in file
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      trackArray[c] += 1;
    }
  }

  // find which char e
  int n = 0;
  for (int i = 0; i < 26; i++) {
    if (trackArray[i] > current_max) {
      current_max = trackArray[i];
      n = i;
    }
  }

  // find key relative to e
  key = n - 4;
  if (key < 0) {
    key += 26;
  }
  if (key >= 26) {
    key -= 26;
  }
  return key;
}

int main(int argc, char ** argv) {
  // fail = print fitting message + EXIT_FAILURE
  if (argc != 2) {
    fprintf(stderr, "Something");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("No input file");
    return EXIT_FAILURE;
  }

  int key = crack(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }

  if ((key < 0) || (key > 26)) {
    perror("Key is out of acceptable range");
    return EXIT_FAILURE;
  }

  // success = print single line stdout w/ key (number of shifts)
  fprintf(stdout, "%d\n", key);
  return EXIT_SUCCESS;
}
