#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

// print function
void output(char ** lines, char * curr, size_t sz, size_t i, size_t j) {
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
}
// getline function + sort
void file_run(char ** lines, char * curr, size_t sz, size_t i, FILE * f) {
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  output(lines, curr, sz, i, 0);
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  // initialize vars
  // char ** lines = NULL;
  // char * curr = NULL;
  // size_t sz;
  // size_t i = 0;

  // read from standard input
  if (argc == 1) {
    file_run(NULL, NULL, 0, 0, stdin);
    return EXIT_SUCCESS;
  }

  // read from file(s)
  if (argc > 1) {
    for (int i = 1; i <= (argc - 1); i++) {
      // open file
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
      }
      file_run(NULL, NULL, 0, 0, f);

      // close file
      if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file\n");
        return EXIT_FAILURE;
      }
    }
    // exit success
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "No files/inputs were run\n");
  return EXIT_FAILURE;
}
