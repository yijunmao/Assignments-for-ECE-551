#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int getNthBit(uint32_t number, int bit) {
  if (bit < 0 || bit >= 32) {
    printf("Bit %d is invalid\n", bit);
    exit(EXIT_FAILURE);
  }
  return (number & (1 << bit)) != 0;
}

void singlenumToBits(uint32_t number, int * p) {
  for (int i = 31; i >= 0; i--) {
    *p = getNthBit(number, i);
    p++;
  }
}

void numToBits(uint32_t * nums, int nNums, int * bits, int nBits) {
  size_t numspace = 32 * nNums;
  size_t Bitspace = nBits;
  if (numspace > Bitspace) {
    printf("Invalid call to numToBits! nBits is %d, nNums is %d\n", nBits, nNums);
    return;
  }
  else if (nNums != 0) {
    uint32_t * p1 = nums;
    int * p2 = bits;
    singlenumToBits(*p1, p2);
    for (int i = 1; i < nNums; i++) {
      p1++;
      p2 += 32;
      singlenumToBits(*p1, p2);
      /*for (int i = 0; i < nNums; i++) {
      for (int j = 31; j >= 0; j--) {
        bits[i * 32 + 31 - j] = getNthBit(nums[i], j);
      }
    }
    }*/
    }
  }
}

void doTest(uint32_t * nums, int n) {
  int bits[n * 32];
  numToBits(nums, n, bits, n * 32);
  for (int i = 0; i < n; i++) {
    printf(" %9d (%8X) => ", nums[i], nums[i]);
    for (int j = 0; j < 32; j++) {
      printf("%d", bits[i * 32 + j]);
    }
    printf("\n");
  }
}

int main(void) {
  uint32_t array1[] = {1, 2, 3, 4, 5, 15, 109};
  uint32_t array2[] = {123456789, 987654321};
  uint32_t array3[] = {1};
  int bits[7 * 32 - 1];
  doTest(array1, 7);
  doTest(array2, 2);
  doTest(array3, 0);
  numToBits(array1, 7, bits, 7 * 32 - 1);
  return EXIT_SUCCESS;
}
