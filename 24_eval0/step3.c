//This file is for Step 3.
//You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write count_neg_seq3_range
//  Step 3 (D): add test cases to main to test count_neg_seq3_range
//
// Be sure to #include any header files you need!

// including necessary header files
#include <stdio.h>
#include <stdlib.h>

// Step 3 (A): write seq3
int seq3(int x, int y) {
  // initialize scaler
  int x_scale = 0;

  // start at center x = 0, y = 0, seq3 = -1
  int answer = -1;

  // find scaling along x based on distance from y = -4
  x_scale = y + 4;

  // iterate to find vertical position
  if (y < 0) {
    for (int s = 0; s > y; s--) {
      answer += 1;
    }
  }
  if (y > 0) {
    for (int s = 0; s < y; s++) {
      answer -= 1;
    }
  }

  // iterate to find horizontal position
  if (x > 0) {
    for (int d = 0; d < x; d++) {
      answer += x_scale;
    }
  }
  if (x < 0) {
    for (int d = 0; d > x; d--) {
      answer -= x_scale;
    }
  }

  return answer;
}

// Step 3 (C): write count_neg_seq3_range
int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi) {
  // counter of # neg numbers
  int counter = 0;

  // corner case where xLow >= xHi or yLow >= yHi (empty sets)
  if ((xLow >= xHi) || (yLow >= yHi)) {
    return counter;
  }

  // count neg #s in search area
  for (int n = xLow; n < xHi; n++) {
    for (int i = yLow; i < yHi; i++) {
      int coord = seq3(n, i);
      if (coord < 0) {
        counter += 1;
      }
    }
  }

  return counter;
}

// Step 3 (B) + (D)
int main(void) {
  // test cases for seq3"
  //-----------------------
  // test for 0, 0
  printf("seq3(%d, %d) = %d\n", 0, 0, seq3(0, 0));

  // test for 0, -1
  printf("seq3(%d, %d) = %d\n", 0, -1, seq3(0, -1));

  // test x = 1
  printf("seq3(%d, %d) = %d\n", 1, -1, seq3(1, -1));

  // test y = -4
  printf("seq3(%d, %d) = %d\n", 0, -4, seq3(0, -4));

  // test both pos
  printf("seq3(%d, %d) = %d\n", 4, 5, seq3(4, 5));

  // test both neg
  printf("seq3(%d, %d) = %d\n", -5, -5, seq3(-5, -5));

  // test pos, neg
  printf("seq3(%d, %d) = %d\n", 5, -5, seq3(5, -5));

  // test neg, pos
  printf("seq3(%d, %d) = %d\n", -5, 5, seq3(-5, 5));

  // test x pos, y 0
  printf("seq3(%d, %d) = %d\n", 4, 0, seq3(4, 0));

  // test cases for count_neg_seq3_range:
  // --------------------------------------
  // test for emtpy search range x
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         2,
         2,
         4,
         6,
         count_neg_seq3_range(2, 2, 4, 6));

  // test for empty search range y
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         4,
         6,
         4,
         4,
         count_neg_seq3_range(4, 6, 4, 4));

  // test for all pos (no neg present)
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         2,
         4,
         4,
         6,
         count_neg_seq3_range(2, 4, 4, 6));

  // test for all neg
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -5,
         -2,
         -5,
         -2,
         count_neg_seq3_range(-5, -2, -5, -2));

  // test for pos, pos, pos, neg
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         2,
         5,
         5,
         -2,
         count_neg_seq3_range(2, 5, 5, -2));

  // test for pos, pos, neg, neg
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         2,
         5,
         -5,
         -3,
         count_neg_seq3_range(2, 5, -5, -3));

  // test for pos, neg, neg, neg
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         5,
         -2,
         -2,
         -5,
         count_neg_seq3_range(5, -2, -2, -5));

  // test for neg, neg, neg, pos
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -5,
         -2,
         -5,
         2,
         count_neg_seq3_range(-5, -2, -5, 2));

  // test for neg, neg, pos, pos
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -5,
         -2,
         2,
         5,
         count_neg_seq3_range(-5, -2, 2, 5));

  // test for neg, pos, pos, pos
  printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",
         -5,
         2,
         2,
         5,
         count_neg_seq3_range(-5, 2, 2, 5));

  return 0;
}
