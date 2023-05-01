#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  //corner cases
  if (inputName == NULL) {
    return ".counts";
  }

  // get length of input
  int input_length = strlen(inputName);

  // create length of output
  int output_length = input_length + 7;

  // allocate memory for new file name
  char * output_name = malloc((output_length + 1) * sizeof(*output_name));

  // add entries to new file name
  for (int i = 0; i < input_length; i++) {
    output_name[i] = inputName[i];
  }

  // add suffix
  char * suffix = ".counts\0";
  for (int i = 0; i < 7; i++) {
    output_name[i + input_length] = suffix[i];
  }
  output_name[output_length] = '\0';

  return output_name;
}
