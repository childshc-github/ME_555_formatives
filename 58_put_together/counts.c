#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  // allocate memory for count array
  counts_t * counting_array = malloc(sizeof(*counting_array));
  counting_array->count_array = 0;
  counting_array->length_count_array = 0;
  counting_array->num_unknown_names = 0;

  return counting_array;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  // if name unknown (NULL)
  if (name == NULL) {
    c->num_unknown_names++;
  }

  // if name known
  else {
    // if name struct already exists, update it with count
    for (int i = 0; i < c->length_count_array; i++) {
      if (strcmp(name, c->count_array[i].count_name) == 0) {
        c->count_array[i].count++;
        return;
      }
    }

    // if name struct doesn't exist, make
    // update array length
    c->length_count_array++;

    // position of struct and name length
    int index = c->length_count_array - 1;
    int name_length = strlen(name);

    // create (realloc memory)
    c->count_array =
        realloc(c->count_array, (c->length_count_array) * sizeof(*c->count_array));
    // c->count_array[index].count_name =
    //     realloc(c->count_array[index].count_name, (name_length) * sizeof(name_length));

    // update values
    c->count_array[index].count = 1;
    char * word = strndup(name, name_length);
    c->count_array[index].count_name = word;
    // strncpy(c->count_array[index].count_name, name, (name_length + 1));
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  // loop through structs + print in order added
  for (int i = 0; i < c->length_count_array; i++) {
    fprintf(outFile, "%s", c->count_array[i].count_name);
    fprintf(outFile, ": %d\n", c->count_array[i].count);
  }

  // print unknown if in dataset
  if (c->num_unknown_names > 0) {
    fprintf(outFile, "<unknown> : ");
    fprintf(outFile, "%d\n", c->num_unknown_names);
  }

  // close file + checks
  if (fclose(outFile) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  // free count + name in one_count_t
  for (int i = 0; i < c->length_count_array; i++) {
    free(c->count_array[i].count_name);
  }

  // free array
  free(c->count_array);

  // free c
  free(c);
}
