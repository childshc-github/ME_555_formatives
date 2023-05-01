#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  // corner case
  if (str == NULL) {
    return;
  }

  //find length of str
  int length = 0;
  int tracker = 0;

  while (str[tracker] != '\0') {
    length++;
    tracker++;
  }

  // make a swapped copy of array for reference
  char tArray[length];
  for (int s = 0; s < length; s++) {
    tArray[(length - s - 1)] = str[s];
  }

  // swap str array in place
  for (int a = 0; a < length; a++) {
    str[a] = tArray[a];
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
