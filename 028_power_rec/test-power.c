#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

unsigned power_myj(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (y < 0) {
    return 0;
  }
  else {
    return x * power_myj(x, y - 1);
  }
}

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned result;
  result = power(x, y);
  expected_ans = power_myj(x, y);
  if (result != expected_ans) {
    printf("power function failed to produce expected answer!\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  // initialize
  unsigned x = 0;
  unsigned y = 0;
  unsigned expected_ans = 0;
  // test case 1
  x = 3;
  y = 4;
  run_check(x, y, expected_ans);
  // test case 2
  x = 3;
  y = 0;
  run_check(x, y, expected_ans);
  // test case 3
  /*x = 3;
  y = -4;
  run_check(x, y, expected_ans);*/
  // test case 4
  x = 0;
  y = 2;
  run_check(x, y, expected_ans);
  // test case 5
  x = 0;
  y = 0;
  run_check(x, y, expected_ans);
  // test case 6
  /*x = 0;
  y = -3;
  run_check(x, y, expected_ans);*/
  // test case 7
  x = -2;
  y = 3;
  run_check(x, y, expected_ans);
  // test case 8
  x = -2;
  y = 0;
  run_check(x, y, expected_ans);
  // test case 9
  /*x = -2;
  y = -3;
  run_check(x, y, expected_ans);*/
  // test case 10
  x = -2;
  y = 2;
  run_check(x, y, expected_ans);
  // test case 11
  /*x = -2;
    y = -4;
  run_check(x, y, expected_ans);*/
  // all test cases passed
  return EXIT_SUCCESS;
}
