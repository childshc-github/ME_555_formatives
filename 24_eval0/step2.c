//This file is for Step 2.
//You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sum_seq2
//  Step 2 (D): add test cases to main to test sum_seq2
//
// Be sure to #include any header files you need!

// including necessary header files
#include <stdio.h>
#include <stdlib.h>

// Step 2 (A): write seq2
int seq2(int x) {
  // initialize answer at pattern's symmetrical center: x = 2 (seq2(x) = -2)
  int answer = -2;

  // checks if at center x = 2
  if (x == 2) {
    return answer;
  }

  // handles corner case of x = 0
  if (x == 0) {
    answer = 2;
    return answer;
  }

  // handles corner case of x = 1
  if (x == 1) {
    answer = -1;
    return answer;
  }

  // if x neg, converts to pos and readjusts "center" to align with correlated pos value
  if (x < 0) {
    x = (x * -1) + 4;
  }

  // use adder initialized at 1 (takes care of x = 1 or 3 adding unusual +1) to track
  int adder = 1;

  // adds +2s relative to adder via loop
  for (int t = 2; t < x; t++) {
    answer += adder;
    adder += 2;
  }
  return answer;

  return EXIT_FAILURE;
}

//  Step 2 (C): write sum_seq2
int sum_seq2(int low, int high) {
  // initialize sum at 0
  int total = 0;

  // checks if low >= high
  if (low >= high) {
    return total;
  }

  // sums range from low (inclusive) to high (exclusive)
  for (int n = low; n < high; n++) {
    total += seq2(n);
  }
  return total;
}

// Step 2 (B): write main to test seq2 + Step 2 (D): add test cases to main to test sum_seq2

int main(void) {
  // test cases for seq2:
  // --------------------
  // test for x = 0
  printf("seq2(%d) = %d\n", 0, seq2(0));

  // test for x = 2
  printf("seq2(%d) = %d\n", 2, seq2(2));

  // test for x = 1
  printf("seq2(%d) = %d\n", 1, seq2(1));

  // test for x = 3
  printf("seq2(%d) = %d\n", 3, seq2(3));

  // test for neg number
  printf("seq2(%d) = %d\n", -3, seq2(-3));

  // test for pos number
  printf("seq2(%d) = %d\n", 5, seq2(5));

  // test for large neg number
  printf("seq2(%d) = %d\n", -50, seq2(-50));

  // test for large pos number
  printf("seq2(%d) = %d\n", 50, seq2(50));

  // test cases for sum_seq2:
  // --------------------------
  // test for 0 and 2 (given example)
  printf("sum_seq2(%d, %d) = %d\n", 0, 2, sum_seq2(0, 2));

  // test for 3 and 6 (given example)
  printf("sum_seq2(%d, %d) = %d\n", 3, 6, sum_seq2(3, 6));

  // test for pos, pos
  printf("sum_seq2(%d, %d) = %d\n", 5, 9, sum_seq2(5, 9));

  // test for pos, neg
  printf("sum_seq2(%d, %d) = %d\n", 5, -7, sum_seq2(5, -7));

  // test for neg, pos
  printf("sum_seq2(%d, %d) = %d\n", -7, 5, sum_seq2(-7, 5));

  // test for neg, neg (low < high)
  printf("sum_seq2(%d, %d) = %d\n", -20, -10, sum_seq2(-20, -10));

  // test for neg, neg (low > high)
  printf("sum_seq2(%d, %d) = %d\n", -10, -20, sum_seq2(-10, -20));

  // test for large neg, large pos (low < high)
  printf("sum_seq2(%d, %d) = %d\n", -100, 100, sum_seq2(-100, 100));

  // test for large pos, large neg (low > high)
  printf("sum_seq2(%d, %d) = %d\n", 100, -100, sum_seq2(100, -100));

  // test for range size of 1 w/ pos
  printf("sum_seq2(%d, %d) = %d\n", 5, 6, sum_seq2(5, 6));

  // test for range size of 1 w/ neg
  printf("sum_seq2(%d, %d) = %d\n", -6, -5, sum_seq2(-6, -5));

  return 0;
}
