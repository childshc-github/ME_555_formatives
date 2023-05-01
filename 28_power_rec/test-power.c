// test cases for power function (x to the y power, both unsigned)
// pass all cases = EXIT_SUCCESS
// fails any case = EXIT_FAILURE

#include <stdio.h>
#include <stdlib.h>

// prototype for power
unsigned power(unsigned x, unsigned y);

// helper fxn
void run_check(unsigned x, unsigned y, unsigned expect_ans) {
  if (power(x, y) != expect_ans) {
    printf("Test failed for x = %d, y = %d\n", x, y);
    exit(EXIT_FAILURE);
  }
}

//main fxn
int main(void) {
  // check for y to x power (wrong)
  run_check(1, 3, 1);

  // check for x to y power (right)
  run_check(3, 1, 3);

  // check for 0 to 0 input
  run_check(0, 0, 1);

  // check for 0 power
  run_check(5, 0, 1);

  // check for 0 denominator
  run_check(0, 5, 0);

  // check for signed int y
  run_check(1, -2, 1);

  // check for signed int x
  run_check(-2, 2, 4);

  // check
  run_check(-2, 3, -8);

  return EXIT_SUCCESS;
}
