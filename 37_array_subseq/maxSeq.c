#include <stdio.h>
#include <stdlib.h>

// maxSeq function
size_t maxSeq(int * array, size_t n) {
  // intialize counter
  size_t max_counter = 0;
  size_t counter = 1;

  // corner cases
  if (n == 0) {
    counter = 0;
    return counter;
  }

  if (n == 1) {
    return counter;
  }

  // iterate through and count
  for (int i = 1; i < n; i++) {
    int val1 = array[(i - 1)];
    int val2 = array[i];
    // conditionals
    if (val1 < val2) {
      counter += 1;
    }
    else if (val1 >= val2) {
      if (counter > max_counter) {
        max_counter = counter;
        counter = 1;
      }
      else if (counter <= max_counter) {
        counter = 1;
      }
    }
  }

  // make sure correct max set
  if (counter > max_counter) {
    max_counter = counter;
  }

  return max_counter;
}
