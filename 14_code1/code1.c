int max(int num1, int num2) {
  int answer = 0;
  // check if num1 is greater than num2
  if (num1 > num2) {
    // if so, your answer is num1
    answer = num1;
  }
  // otherwise, your answer is num2
  else {
    answer = num2;
  }

  return answer;
}

int main(void) {
  printf("max(42, -69) is %d\n", max(42, -69));
  printf("max(33, 0) is %d\n", max(33, 0));
  printf("max(0x123456, 123456) is %d\n", max(0x123456, 123456));
  // print the max of 0x451215AF and 0x913591AF and prints it out as a decimal number
  printf("max(0x451215AF, 0x913591AF) is %d\n", max(0x451215AF, 0x913591AF));
  return 0;
}
