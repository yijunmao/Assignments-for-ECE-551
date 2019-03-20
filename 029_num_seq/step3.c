// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!

#include <stdio.h>
#include <stdlib.h>

// Step 3 (A): write seq3
int seq3(int x, int y) {
  return -3 * x + 2 * y + x * y;
}

// Step 3 (C): write countEvenInSeq3Range
int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  if (xHi <= xLow || yHi <= yLow) {
    return 0;
  }
  else {
    int IsEven = 0;
    for (int i = xLow; i < xHi; i++) {
      for (int j = yLow; j < yHi; j++) {
        if (seq3(i, j) % 2 == 0) {
          IsEven += 1;
        }
      }
    }
    return IsEven;
  }
}

// Step 3 (B): write main to test seq3
int main(void) {
  // Test case 1 of seq3
  int x = 0;
  int y = 0;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 2 of seq3
  x = 5;
  y = 0;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 3 of seq3
  x = -4;
  y = 0;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 4 of seq3
  x = 0;
  y = 3;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 5 of seq3
  x = 0;
  y = -5;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 6 of seq3
  x = 4;
  y = 5;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 7 of seq3
  x = -4;
  y = -5;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 8 of seq3
  x = 3;
  y = -2;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 9 of seq3
  x = -3;
  y = 2;
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));

  // Test case 1 of countEvenInSeq3Range
  int xLow = 0;
  int xHi = 0;
  int yLow = -5;
  int yHi = 3;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 2 of countEvenInSeq3Range
  xLow = 7;
  xHi = -3;
  yLow = -2;
  yHi = 4;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 3 of countEvenInSeq3Range
  xLow = -3;
  xHi = -2;
  yLow = 4;
  yHi = 4;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 4 of countEvenInSeq3Range
  xLow = -5;
  xHi = 4;
  yLow = 3;
  yHi = 0;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 5 of countEvenInSeq3Range
  xLow = -4;
  xHi = -4;
  yLow = 3;
  yHi = -1;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 6 of countEvenInSeq3Range
  xLow = 3;
  xHi = -1;
  yLow = 2;
  yHi = 2;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 7 of countEvenInSeq3Range
  xLow = -4;
  xHi = -5;
  yLow = 5;
  yHi = 2;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 8 of countEvenInSeq3Range
  xLow = -3;
  xHi = 5;
  yLow = -2;
  yHi = 4;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 9 of countEvenInSeq3Range
  xLow = 0;
  xHi = 4;
  yLow = -3;
  yHi = 0;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  // Test case 10 of countEvenInSeq3Range
  xLow = 2;
  xHi = 5;
  yLow = -5;
  yHi = -2;
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",
         xLow,
         xHi,
         yLow,
         yHi,
         countEvenInSeq3Range(xLow, xHi, yLow, yHi));

  return EXIT_SUCCESS;
}
