#include "rand_story.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// check formatting of given name of file
void format_checker(char * fname) {
  // open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // initialize memory
  char * curr = NULL;
  size_t sz = 0;

  // loop through + find underscores
  while (getline(&curr, &sz, f) >= 0) {
    // initialize number of blanks counter
    int blank_count = 0;

    // get length of current line
    int curr_length = strlen(curr);

    // count number of blanks on current line
    for (int i = 0; i < curr_length; i++) {
      if (curr[i] == '_') {
        blank_count++;
      }
    }

    // make sure all blanks have closing blank
    if (((blank_count % 2) != 0) && (blank_count != 0)) {
      fprintf(stderr, "Unmatched underscore present.\n");
      exit(EXIT_FAILURE);
    }
  }
  free(curr);

  // check file closes
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }
}

// creates catarry_t
catarray_t * create_catarray(void) {
  // allocate memory for catarray entries
  catarray_t * story_stats = malloc(sizeof(*story_stats));
  story_stats->n = 0;
  story_stats->arr = 0;

  return story_stats;
}

// frees catarry_t
void free_catarry(catarray_t * stats) {
  // free category_t
  for (int i = 0; i < stats->n; i++) {
    for (int s = 0; s < stats->arr[i].n_words; s++) {
      // free words in words array
      free(stats->arr[i].words[s]);
    }
    // free word array
    free(stats->arr[i].words);

    // free name
    free(stats->arr[i].name);
  }

  // free catarray
  free(stats->arr);

  // free array
  free(stats);
}

// format check category files for proper ":" placement
void category_checker(char * fname) {
  // open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // initialize
  char * curr = NULL;
  size_t sz = 0;

  // loop through and find ":"
  while (getline(&curr, &sz, f) >= 0) {
    // make sure only one ":" on line
    int counter = 0;
    for (int i = 0; i < strlen(curr); i++) {
      if (curr[i] == ':') {
        counter++;
      }
    }

    if (counter == 0) {
      fprintf(stderr, "No colon on line.\n");
      exit(EXIT_FAILURE);
    }
    if (counter > 1) {
      fprintf(stderr, "More than one colon on line.\n");
      exit(EXIT_FAILURE);
    }

    // check category + word
    char * start = strchr(curr, ':');
    int length_category = start - curr;
    int length_word = strlen(curr) - length_category - 2;

    // make sure category exists
    if (length_category <= 0) {
      fprintf(stderr, "No category given.\n");
      exit(EXIT_FAILURE);
    }

    // make sure word exists
    if (length_word <= 0) {
      fprintf(stderr, "No word given for category.\n");
      exit(EXIT_FAILURE);
    }
  }
  free(curr);

  // check file closes
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }
}

// parses category:word file and creates a catarray_t
catarray_t * readCW(char * fname) {
  // check file format
  category_checker(fname);

  // open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // get memory
  category_t * stats = malloc(0 * sizeof(*stats));

  // loop through file
  int length_stats = 0;
  char * curr = NULL;
  size_t sz = 0;

  // loop through file
  while (getline(&curr, &sz, f) >= 0) {
    // get category (name)
    char * start = strchr(curr, ':');
    int length_category = start - curr;
    int length_word = strlen(curr) - length_category - 2;
    char * category = strndup(curr, length_category);

    // get word
    start++;
    char * word = strndup(start, length_word);

    // add null terminator
    category[length_category] = '\0';
    word[length_word] = '\0';

    // if struct for category already exists
    int exists = 0;
    for (int i = 0; i < length_stats; i++) {
      if (strcmp(category, stats[i].name) == 0) {
        // update tracker
        exists = 1;

        // get index for word entry
        size_t index = stats[i].n_words;

        // get more memory for word array
        stats[i].words = realloc(stats[i].words, (index + 1) * sizeof(*stats[i].words));

        // update word array
        stats[i].words[index] = word;

        // update struct
        stats[i].n_words++;

        // free unused pointer
        free(category);
      }
    }

    // if struct for category doesn't exist
    if (exists == 0) {
      // get more struct memory
      stats = realloc(stats, (length_stats + 1) * sizeof(*stats));

      // get memory for word array
      char ** entry = malloc(sizeof(*entry));

      // update word array
      entry[0] = word;
      stats[length_stats].words = entry;

      // update struct
      stats[length_stats].name = category;
      stats[length_stats].n_words = 1;

      length_stats++;
    }
  }
  free(curr);

  // add structs to catarray_t
  catarray_t * answer = malloc(sizeof(*answer));
  answer->n = length_stats;
  answer->arr = stats;

  // close file
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }

  // return completed catarray_t
  return answer;
}

// checks if given characters are valid backreference numbers via ASCII
int is_numbers(char * input, int length_input) {
  // exclude null terminator
  length_input--;

  // loop through category
  for (int i = 0; i < length_input; i++) {
    if ((i == 0) && (input[i] == 48)) {
      // not a valid backreference if first entry is int 0
      return 0;
    }
    if ((input[i] < 48) || (input[i] > 57)) {
      // if any not a number, fail (accounts for mixed types)
      return 0;
    }
  }

  // if all are numbers
  return 1;
}

// convert array of char -> int type
int convert_numbers(char * input, int length_input) {
  // ignore null terminator
  length_input--;

  // get power of tens scale
  int scaler = 1;
  int total = 0;
  for (int s = 1; s < length_input; s++) {
    scaler = scaler * 10;
  }

  // get int
  for (int i = 0; i < length_input; i++) {
    // get converted number
    unsigned num = input[i] - '0';

    // update scaler + answer
    total = total + (num * scaler);
    scaler = scaler / 10;
  }

  // return calculated int
  return total;
}

// frees backref array
void free_backref(char ** array, int length_array) {
  for (int i = 0; i < length_array; i++) {
    // free entries
    free(array[i]);
  }
  // free array
  free(array);
}

// print story to stdout
void print_story(char * fname, catarray_t * carr) {
  // open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  // initialize memory
  char * curr = NULL;
  size_t sz = 0;

  // create array for tracking backreferences
  char ** backrefs = malloc(sizeof(*backrefs));
  int length_backrefs = 0;

  // loop through + find underscores
  while (getline(&curr, &sz, f) >= 0) {
    // tracking variables
    int start = 0;
    int end = 1;
    int length = strlen(curr);

    // loop through + print
    for (int i = 0; i < length; i++) {
      // if end of curr, print newline
      if (curr[i] == '\n') {
        printf("\n");
      }

      // if not a blank don't modify
      else if (curr[i] != '_') {
        printf("%c", curr[i]);
      }

      // if a blank
      else if (curr[i] == '_') {
        // find next underscore
        start = i;
        end = 1;
        int index = start + end;
        while (curr[index] != '_') {
          index++;
          end++;
        }

        // get index of next underscore (end of current category)
        end += start;

        // get name of blank
        int size = end - start;
        char * name = malloc(size * sizeof(*name));
        for (int s = (start + 1); s < end; s++) {
          int place = s - start - 1;
          name[place] = curr[s];
        }
        name[(size - 1)] = '\0';

        // update for next iteration (won't check inside blank again)
        int increment = end - start;
        i += increment;

        // check if backreference is valid and print
        if (is_numbers(name, size) == 1) {
          // get blank in int type
          unsigned back = convert_numbers(name, size);

          // error check (out of array)
          if (back > length_backrefs) {
            fprintf(stderr, "Backreference is out of array bounds.\n");
            exit(EXIT_FAILURE);
          }

          // get backref reference location
          int backref_loc = length_backrefs - back;

          // get previous print from array
          int l_b = strlen(backrefs[backref_loc]);
          char * old_blank = strndup(backrefs[backref_loc], l_b);

          // print
          printf("%s", old_blank);

          // get memory for word array
          backrefs = realloc(backrefs, (length_backrefs + 1) * sizeof(*backrefs));

          // update word array
          backrefs[length_backrefs] = old_blank;
          length_backrefs++;
        }

        // if not backreference, add to backref array + print
        else if (is_numbers(name, size) == 0) {
          // get memory for word array
          backrefs = realloc(backrefs, (length_backrefs + 1) * sizeof(*backrefs));

          // get random word
          const char * random_word = chooseWord(name, carr);

          // update word array
          int rand_length = strlen(random_word);
          char * rand_cpy = strndup(random_word, rand_length);
          backrefs[length_backrefs] = rand_cpy;
          length_backrefs++;

          // print
          printf("%s", random_word);
        }

        // free blank name
        free(name);
      }
    }
  }
  free(curr);
  free_backref(backrefs, length_backrefs);

  // check file closes
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file\n");
    exit(EXIT_FAILURE);
  }
}
