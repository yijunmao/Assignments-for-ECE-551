#include "IntArray.h"

#include <assert.h>

#include <ostream>

IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs) :
    data(new int[rhs.numElements]),
    numElements(rhs.numElements) {
  for (int i = 0; i < rhs.numElements; i++) {
    data[i] = rhs.data[i];
  }
}

IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs) {
    int * temp = new int[rhs.numElements];
    for (int i = 0; i < rhs.numElements; i++) {
      temp[i] = rhs.data[i];
    }
    delete[] data;
    numElements = rhs.numElements;
    data = temp;
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index >= 0 && index < numElements);
  return data[index];
}

// operator is different as a function, [] originally takes a parameter in it, so overloading will not change that
int & IntArray::operator[](int index) {
  assert(index >= 0 && index < numElements);
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return 0;
  }
  for (int i = 0; i < rhs.numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return 0;
    }
  }
  return 1;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return 1;
  }
  for (int i = 0; i < rhs.numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return 1;
    }
  }
  return 0;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }
  if (rhs.size() != 0) {
    s << rhs[rhs.size() - 1] << "}";
  }
  else {
    s << "}";
  }

  return s;
}
