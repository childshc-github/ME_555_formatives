#include "kv.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  //open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // allocate memory (kv_pair struct)
  kvpair_t * pairs = malloc(0 * sizeof(*pairs));

  // initialize
  int length_of_pairs = 0;
  char * curr = NULL;
  size_t sz = 0;
  // const char s[2] = "=";

  // loop through file until end of key
  while (getline(&curr, &sz, f) >= 0) {
    /* get the first token */
    // char * token = strtok(curr, s);
    // if (token == NULL) {
    //   fprintf(stderr, "No key given.\n");
    //   exit(EXIT_FAILURE);
    // }
    // // duplicate key
    // char * key = strdup(token);

    // get/check value
    char * start = strchr(curr, '=');
    int length_key = start - curr;
    int length_value = strlen(curr) - length_key;
    char * key = strndup(curr, length_key);
    start++;
    length_value = length_value - 2;
    char * value = strndup(start, length_value);

    // add to pairs
    pairs = realloc(pairs, (length_of_pairs + 1) * sizeof(*pairs));
    pairs[length_of_pairs].key = key;
    pairs[length_of_pairs].value = value;
    length_of_pairs++;
    free(curr);
    curr = NULL;
  }
  free(curr);

  kvarray_t * answer = malloc(sizeof(*answer));

  answer->kvpA = pairs;
  answer->kvpA_length = length_of_pairs;

  // close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }

  return answer;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->kvpA_length; i++) {
    free(pairs->kvpA[i].key);
    free(pairs->kvpA[i].value);
  }
  free(pairs->kvpA);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i = 0; i < pairs->kvpA_length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpA[i].key, pairs->kvpA[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i = 0; i < pairs->kvpA_length; i++) {
    if (strcmp(key, pairs->kvpA[i].key) == 0) {
      return pairs->kvpA[i].value;
    }
  }
  return NULL;
}
