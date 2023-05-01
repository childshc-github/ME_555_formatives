//This file is for Step 1.
//You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write print_seq1_range
//  Step 1 (D): add test cases to main to test print_seq1_range
//
// Be sure to #include any header files you need!

// including necessary header files
#include <stdio.h>
#include <stdlib.h>

// Step 1 (A): write seq1
// Note: Only *returns* value + works for values outside shown
// Pattern: seq1(x) varies by +/-3 for every +/-x

int seq1(int x) {
  // initialize answer at x = 0 (seq(1) = -5)
  int answer = -5;

  // check if x is 0, positive, or negative --> add/dec by 3
  if (x == 0) {
    return answer;
  }

  else if (x > 0) {
    for (int p = 0; p < x; p++) {
      answer += 3;
    }
    return answer;
  }

  else if (x < 0) {
    for (int n = 0; n < (x * -1); n++) {
      answer -= 3;
    }
    return answer;
  }

  return EXIT_FAILURE;
}

// Step 1 (C): write print_seq1_range

void print_seq1_range(int low, int high) {
  // given low, find the lower bound: seq1(low)
  int lower_bound = seq1(low);

  // given high, find the upper bound: seq1(high)
  int upper_bound = seq1(high);

  // corner case handling if lower_bound >= upper_bound
  if (lower_bound >= upper_bound) {
    printf("\n");
  }

  // Iterate from lower --> (upper - 3), adding +3 each loop w/ commas
  else {
    for (int n = lower_bound; n < (upper_bound - 3); (n += 3)) {
      printf("%d, ", n);
    }

    // printf last entry w/ no comma and a newline
    printf("%d\n", (upper_bound - 3));
  }
}

// Step 1 (B): write main to test seq1 + Step 1 (D): add test cases to main to test print_seq1_range

int main(void) {
  // test cases for seq(x):
  // ---------------------
  // test for 0 entry
  printf("seq1(%d) = %d\n", 0, seq1(0));

  // test for a negative number
  printf("seq1(%d) = %d\n", -2, seq1(-2));

  // test for a positive number
  printf("seq1(%d) = %d\n", 2, seq1(2));

  // test for very large positive number
  printf("seq1(%d) = %d\n", 1000, seq1(1000));

  // test for very large negative number
  printf("seq1(%d) = %d\n", -1000, seq1(-1000));

  // test cases for print_seq1_range:
  // --------------------------------
  // test for 0, 0 entry
  printf("print_seq1_range(%d, %d)\n", 0, 0);
  print_seq1_range(0, 0);

  // test for expected entry (high > low)
  printf("print_seq1_range(%d, %d)\n", -3, 3);
  print_seq1_range(-3, 3);

  // test for pos low, pos high
  printf("print_seq1_range(%d, %d)\n", 2, 8);
  print_seq1_range(2, 8);

  // test for pos low, neg high (low > high)
  printf("print_seq1_range(%d, %d)\n", 4, -2);
  print_seq1_range(4, -2);

  // test for neg low, neg high (low < high)
  printf("print_seq1_range(%d, %d)\n", -10, -5);
  print_seq1_range(-10, -5);

  // test for neg low, neg high (low > high)
  printf("print_seq1_range(%d, %d)\n", -10, -13);
  print_seq1_range(-10, -13);

  // check for large neg low, large pos high (low < high)
  printf("print_seq1_range(%d, %d)\n", -30, 30);
  print_seq1_range(-30, 30);

  return 0;
}
