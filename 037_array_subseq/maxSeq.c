#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0 || n == 1) {
    return n;
  }
  else {
    int LastNumber = array[0];
    int CurrentNumber = array[1];
    size_t MaxInc = 1;
    size_t CurrentInc = 1;
    for (size_t i = 1; i < n; i++) {
      CurrentNumber = array[i];
      LastNumber = array[i - 1];
      if (CurrentNumber > LastNumber) {
        CurrentInc += 1;
        if (CurrentInc > MaxInc) {
          MaxInc = CurrentInc;
        }
      }
      else {
        CurrentInc = 1;
      }
    }
    return MaxInc;
  }
}
