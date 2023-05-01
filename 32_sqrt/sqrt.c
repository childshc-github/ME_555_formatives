#include <stdio.h>
#include <stdlib.h>

int square_root(int x, int * perfect) {
  // WRITE ME
  // if x neg, return -1
  if (x < 0) {
    *perfect = 0;
    return -1;
  }

  // if x 0, return 0
  if (x == 0) {
    *perfect = 1;
    return 0;
  }

  // track +2 of cycle
  int tracker = 1;
  // looper = square root (25 = 5 loops)
  int looper = 0;
  // find difference of x and n for not perfect squares
  int dist = 0;

  // yes perfect square  --> box perfect becomes 1 + return square root of x
  // no perfect square --> box perfect becomes 0 + return largest integer
  for (int n = 1; n < 2147395601; (n += tracker)) {
    tracker += 2;
    looper += 1;
    dist = n - x;
    if (x == n) {
      *perfect = 1;
      return looper;
    }
    if (dist > 0) {
      *perfect = 0;
      return looper - 1;
    }
  }

  return EXIT_FAILURE;
}

/* helper function to call square_root and print whether the input is a 
   perfect square or not */
void test_one(int x) {
  int perfect;
  int rt = square_root(x, &perfect);
  if (perfect) {
    printf("sqrt(%d) is %d, perfect square\n", x, rt);
  }
  else {
    printf("sqrt(%d) is %d, NOT perfect square\n", x, rt);
  }
}

int main(void) {
  test_one(4);
  test_one(5);
  test_one(0);
  test_one(-1);
  test_one(-4);
  // test with the largest int that does not cause any operation in
  // square_root to overflow
  test_one(2147395600);

  // test with the one less than the largest int that does not cause
  // any operation in square_root to overflow
  test_one(2147395599);

  return EXIT_SUCCESS;
}
