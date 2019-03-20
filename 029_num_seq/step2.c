// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!

// Step 2 (A): write seq2
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  return x * x + 3 * x + 1;
}

int sumSeq2(int low, int high) {
  if (low >= high) {
    return 0;
  }
  else {
    int sum = 0;
    for (int i = low; i < high; i++) {
      sum += seq2(i);
    }
    return sum;
  }
}

int main(void) {
  // Test case 1 of seq2
  int x = 14;
  printf("seq2(%d) = %d\n", x, seq2(x));
  // Test case 2 of seq2
  x = 0;
  printf("seq2(%d) = %d\n", x, seq2(x));
  // Test case 3 of seq2
  x = -4;
  printf("seq2(%d) = %d\n", x, seq2(x));
  // Test case 1 of sumSeq2
  int low = 9;
  int high = 7;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 2 of sumSeq2
  low = 0;
  high = -4;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 3 of sumSeq2
  low = 6;
  high = -3;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 4 of sumSeq2
  low = -2;
  high = -2;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 5 of sumSeq2
  low = 0;
  high = 0;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 6 of sumSeq2
  low = 7;
  high = 7;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 7 of sumSeq2
  low = -4;
  high = 5;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  // Test case 8 of sumSeq2
  low = 0;
  high = 8;
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  return EXIT_SUCCESS;
}
