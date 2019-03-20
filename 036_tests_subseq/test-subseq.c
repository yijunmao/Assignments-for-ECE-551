#include <stdio.h>
#include <stdlib.h>

int maxSeq(int array[], int n);

int main(void) {
  // Test case 1
  int array1[] = {1};
  size_t n = 0;
  if (maxSeq(array1, n) != 0) {
    return EXIT_FAILURE;
  }
  // Test case 2
  int array2[] = {1, 1, 2, 3, 4};
  n = 5;
  if (maxSeq(array2, n) != 4) {
    return EXIT_FAILURE;
  }
  // Test case 3
  int array3[] = {1, 2, 2, 3, 4, 5};
  n = 6;
  if (maxSeq(array3, n) != 4) {
    return EXIT_FAILURE;
  }
  // Test case 4
  int array4[] = {1, 0, 2, 0, 3, 0, 4, 0};
  n = 8;
  if (maxSeq(array4, n) != 2) {
    return EXIT_FAILURE;
  }
  // Test case 5
  int array5[] = {-1, 2, 7, 6, 9, 11, 13};
  n = 7;
  if (maxSeq(array5, n) != 4) {
    return EXIT_FAILURE;
  }
  // Test case 6
  int array6[] = {-7, -8, -8, 0, 1, 0, 3, 2, 4};
  n = 9;
  if (maxSeq(array6, n) != 3) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
