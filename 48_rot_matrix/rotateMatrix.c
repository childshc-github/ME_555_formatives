#include <stdio.h>
#include <stdlib.h>

// // check matrix valid (entries + size) function
// void check_size(FILE * f) {
//   // column and row counts
//   int c = 0;
//   int rowc = 0;
//   int columnc = 0;

//   while ((c = fgetc(f)) != EOF) {
//     // row checks
//     rowc++;
//     if (c == '\n') {
//       if (rowc < 11) {
//         fprintf(stderr, "Matrix has too few rows\n");
//         exit(EXIT_FAILURE);
//       }
//       if (rowc > 11) {
//         fprintf(stderr, "Matrix has too many rows\n");
//         exit(EXIT_FAILURE);
//       }
//       columnc++;
//       rowc = 0;
//     }
//   }
//   // column checks
//   if (columnc < 10) {
//     fprintf(stderr, "Matrix has too few columns\n");
//     exit(EXIT_FAILURE);
//   }
//   if (columnc > 10) {
//     fprintf(stderr, "Matrix has too many columns\n");
//     exit(EXIT_FAILURE);
//   }
// }

// rotate CW function
void rotate(FILE * f) {
  // check formatting
  // column and row counts
  int c = 0;
  int rowc = 0;
  int columnc = 0;

  // initialize vars
  int rowtrack = 0;
  int columntrack = 9;
  char fArray[10][10];

  while ((c = fgetc(f)) != EOF) {
    // row checks
    rowc++;
    if (c == '\n') {
      if (rowc < 11) {
        fprintf(stderr, "Matrix has too few rows\n");
        exit(EXIT_FAILURE);
      }
      if (rowc > 11) {
        fprintf(stderr, "Matrix has too many rows\n");
        exit(EXIT_FAILURE);
      }
      columnc++;
      rowc = 0;
    }

    //create arrays of columns using loop

    if (c != '\n') {
      fArray[rowtrack][columntrack] = c;
      rowtrack++;
    }

    if (c == '\n') {
      rowtrack = 0;
      columntrack -= 1;
    }
  }

  // column checks
  if (columnc < 10) {
    fprintf(stderr, "Matrix has too few columns\n");
    exit(EXIT_FAILURE);
  }
  if (columnc > 10) {
    fprintf(stderr, "Matrix has too many columns\n");
    exit(EXIT_FAILURE);
  }

  //print matrix to stdout
  for (int i = 0; i < 10; i++) {
    for (int e = 0; e < 10; e++) {
      printf("%c", fArray[i][e]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Incorrect number on inputs\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file\n");
    return EXIT_FAILURE;
  }

  rotate(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
