#include <assert.h>
#include <math.h>

#include <cstdlib>
#include <iostream>

#include "function.h"

// inherit from class Function<int,int>
/*class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  //constructor
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}

  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};*/

// binary search function
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  //assert(low <= high);

  /*
  too many invokes may not be able to pass the test
  // corner case f(x) is all negative
  if (f->invoke(low) > 0) {
    return low;
  }
  // corner case f(x) is all positive
  else if (f->invoke(high) < 0) {
    return high - 1;
  }
  */

  int count = low;
  int middle;
  int ans;

  // termination condition
  while (low < high) {
    middle = (low + high) / 2;
    /*if (middle == high && f->invoke(middle)>0) {
      return f->invoke(low);
    }
    if (middle == low && f->invoke(middle)<0) {
      return f->invoke(high);
      }*/
    ans = f->invoke(middle);

    if (ans > 0) {
      high = middle;
    }
    else if (ans <= 0) {
      low = middle + 1;
    }
  }
  return low == count ? low : low - 1;  // if low == count return low; else return low - 1
}

// while (low < high) {
// ans = invoke(middle)
// if ans < 0
// bfs(middle, high)
// else
// bfs(low, middle)
