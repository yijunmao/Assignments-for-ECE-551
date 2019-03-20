#include <assert.h>
#include <math.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

extern int binarySearchForZero(Function<int, int> * f, int low, int high);

// class SinFunction
class SinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinFunction : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};

// inherit from class Function<int,int>
class CountedIntFn : public Function<int, int>
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
};

// check if invoke the function an appropriate number of times
void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  // f is a pointer to a SinFunction object
  // check value and number of invocations
  // max allowed number of invocations
  unsigned n;
  if (low < high) {
    n = log2(high - low) + 1;
  }
  else {
    n = 1;
  }
  // declare a CountedIntFn object
  CountedIntFn count(n, f, mesg);

  // check vlaue and number of invocations
  assert(binarySearchForZero(&count, low, high) == expected_ans);
}

// test cases
int main() {
  SinFunction s;
  LinFunction l;

  // check sin function
  check(&s, 0, 150000, 52359, "Sinfunction fails");
  check(&s, 0, 50000, 49999, "Sinfunction fails");
  check(&s, 60000, 150000, 60000, "Sinfuction fails");

  // check linear function
  check(&l, -5, 0, -1, "Linear function fails");
  check(&l, 1, 6, 1, "Linear function fails");
  check(&l, 0, 1, 0, "Linear function fails");
  check(&l, -99999999, 10000000, 0, "Linear function fails");

  return 0;
}
