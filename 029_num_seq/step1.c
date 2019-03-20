// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!

// Header files
#include <stdio.h>
#include <stdlib.h>

// Step 1 (A): write seq1
int seq1(int x) {
  if (x == 0) {
    return -3;
  }
  else if (x == 1) {
    return 1;
  }
  else if (x > 1) {
    return 2 * seq1(x - 1) - seq1(x - 2);
  }
  else {
    return 2 * seq1(x + 1) - seq1(x + 2);
  }
}

// Step 1 (C): write printSeq1Range
void printSeq1Range(int low, int high) {
  if (high <= low) {
    printf("\n");
  }
  else if ((high - low) == 1) {
    printf("%d\n", seq1(low));
  }
  else {
    for (int i = low; i < (high - 1); i++) {
      printf("%d, ", seq1(i));
    }
    printf("%d\n", seq1(high - 1));
  }
}

// Step 1 (B): write main to test seq1
int main(void) {
  // Test case 1 of seq1
  int x = 4;
  printf("seq1(%d) = %d\n", x, seq1(x));
  // Test case 2 of seq1
  x = 0;
  printf("seq1(%d) = %d\n", x, seq1(x));
  // Test case 3 of seq1
  x = -5;
  printf("seq1(%d) = %d\n", x, seq1(x));

  // Test case 1 of printSeq1Range
  int low = 3;
  int high = 3;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 2 of printSeq1Range
  low = 7;
  high = 2;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 3 of printSeq1Range
  low = -4;
  high = 5;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 4 of printSeq1Range
  low = -5;
  high = -5;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 5 of printSeq1Range
  low = 4;
  high = -6;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 6 of printSeq1Range
  low = -2;
  high = -7;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 7 of printSeq1Range
  low = 0;
  high = 5;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 8 of printSeq1Range
  low = -4;
  high = -1;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 9 of printSeq1Range
  low = 2;
  high = 5;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 10 of printSeq1Range
  low = 0;
  high = 0;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  // Test case 11 of printSeq1Range
  low = 0;
  high = -6;
  printf("printSeq1Range(%d, %d)\n", low, high);
  printSeq1Range(low, high);
  return EXIT_SUCCESS;
}

// Step 1 (D): add test cases to main to test printSeq1range
