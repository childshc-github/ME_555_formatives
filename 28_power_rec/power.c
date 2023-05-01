// program for computing x to y power (unsigned) via recursion

#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  unsigned answer = 1;

  // base case
  if (y == 0) {
    return answer;
  }

  // recursion loop
  return x * power(x, y - 1);
}
