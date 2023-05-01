#include <stdio.h>
#include <stdlib.h>

// maxSeq prototype
size_t maxSeq(int * array, size_t n);

// checking function
void checker(int * array, size_t n, size_t answer) {
  size_t actual = maxSeq(array, n);
  if (actual != answer) {
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  // expected input
  int check1[] = {1, 2, 3, 4};
  checker(check1, 4, 4);

  // negative increase
  int check2[] = {-5, -4, -3, 0};
  checker(check2, 4, 4);

  // decreasing
  int check3[] = {5, 4, 3, 0};
  checker(check3, 4, 1);

  // overall change, nested increase
  int check4[] = {1, 3, 0, 3, 4, 5};
  checker(check4, 6, 4);

  // empty
  int check5[] = {};
  checker(check5, 0, 0);

  // repeating nums
  int check6[] = {1, 2, 3, 3};
  checker(check6, 4, 3);

  // repeating nums
  int check7[] = {3, 3, 4, 5};
  checker(check7, 4, 3);

  // all same number
  int check8[] = {3, 3, 3, 3};
  checker(check8, 4, 1);

  exit(EXIT_SUCCESS);
}
