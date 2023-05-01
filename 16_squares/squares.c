//compute max function
int max(int num1, int num2) {
  int answer = 0;
  // check if num1 is greater than num2
  if (num1 >= num2) {
    // if so, your answer is num1
    answer = num1;
  }
  // otherwise, your answer is num2
  else {
    answer = num2;
  }

  return answer;
}


// between fxn
int between(int inside, int b1, int b2) {
  if (inside >= b1) {
    if (inside <= b2) {
      return 1;
    // 1 = true
    }
  }
  return 0;
  // 0 = false
}

// equal to fxn
int is_equal(int inside, int b1, int b2) {
  if (inside == b1) {
    return 1;
  }
  else if (inside == b2) {
    return 1;
  }
  return 0;
}

// less than fxn
int less_than(int inside, int b) { 
  if (inside < b) {
    return 1;
  }
  return 0;
}

// conditions met checker
int cond_met(int check1, int check2, int check3, int check4) {
  if (check1 == 1 && check2 == 1) {
    return 1;
  }
  else if (check3 == 1 && check4 == 1) {
    return 1;
  }
  return 0;
}


void squares(int size1, int x_offset, int y_offset, int size2) {
  // compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, (x_offset + size2));
  // compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, (y_offset + size2));
  // count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
  // count from 0 to w. Call the number you count with x
    for (int x = 0; x < w; x++) {
    
    //check 1 instructions
    // check if EITHER
    //     the point is on a vertical boundary of square 1
    //     ((x is between x_offset  and x_offset +size2) AND
    // check 1a
    //      y is equal to either y_offset OR y_offset + size2 - 1 )
    // check 1b
    //   OR
    //     the point is on a horizontal boundary of square 1
    //     ((y is between y_offset and y_offset + size2) AND
    // check 1c
    //      x is equal to either x_offset OR x_offset + size2 -1)
    // check 1d
    //  if so, print a *

    // check 1
    int a1 = between(x, x_offset, (x_offset + size2));
    int b1 = is_equal(y, y_offset, (y_offset + size2 - 1));
    int c1 = between(y, y_offset, (y_offset + size2));
    int d1 = is_equal(x, x_offset, (x_offset + size2 - 1));
    int check_1 = cond_met(a1, b1, c1, d1);

  // check 2 instructions
  // if not,
  //  check if EITHER
  //     the point is on a vertical boundary of square 2
  //     x is less than size1 
  // check 2a
  // AND (y is either 0 or size1-1)
  // check 2b
  //  OR
  //     the point is on a horizontal boundary of square 2
  //     y is less than size1 
  // check 2c
  // AND (x is either 0 or size1-1)
  // check 2d
  // if so, print a #
  

  // check 2
  int a2 = less_than(x, size1);
  int b2 = is_equal(y, 0, (size1 - 1));
  int c2 = less_than(y, size1);
  int d2 = is_equal(x, 0, size1 - 1);
  int check_2 = cond_met(a2, b2, c2, d2);

  // printing results

  if (check_1 == 1) {
    printf("*");
    }
  else if (check_2 == 1) {
      printf("#");
    }
  else {
    // else print a space
      printf(" ");
    }
  }

  // when you finish counting x from 0 to w,
  // print a newline
  printf("\n");
  }
}