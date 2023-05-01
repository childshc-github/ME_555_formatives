#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  // input = list of names
  // open files + get values via key
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // create counts struct
  counts_t * answer = createCounts();

  // loop through file + find corresponding key
  // initialize
  char * curr = NULL;
  size_t sz = 0;

  // loop through file until end of value
  while (getline(&curr, &sz, f) >= 0) {
    // get key
    char * start = strchr(curr, '\0');
    int length_key = start - curr;
    char * key = strndup(curr, length_key);
    int index = length_key - 1;
    key[index] = '\0';

    // find matching value
    char * value = lookupValue(kvPairs, key);
    free(key);
    // update counts structs
    addCount(answer, value);
    start++;
  }
  free(curr);

  // for (int i = 0; i < answer->length_count_array; i++) {
  //   printf("Answer value is %s with count of %d\n",
  //          answer->count_array[i].count_name,
  //          answer->count_array[i].count);
  // }
  // printf("Unknowns have %d entries\n", answer->num_unknown_names);
  // printf("Length of answer is %d\n", answer->length_count_array);
  //close f
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }

  // return counts struct
  return answer;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2) {
    fprintf(stderr, "Inadequate input(s)\n");
    return EXIT_FAILURE;
  }

  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);

  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Could not open file\n");
      exit(EXIT_FAILURE);
    }

    //print the counts from c into the FILE f
    printCounts(c, f);

    //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }

  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
