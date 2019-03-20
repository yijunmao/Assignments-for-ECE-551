#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}

// haven't used numColumns
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows),
    numColumns(rhs.numColumns),
    rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(*rhs.rows[i]);
  }
}

IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(*rhs.rows[i]);
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = temp;
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return 0;
  }
  if (numColumns != rhs.numColumns) {
    return 0;
  }
  for (int i = 0; i < rhs.numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return 0;
    }
  }
  return 1;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix temp(rhs.numRows, rhs.numColumns);
  for (int i = 0; i < numRows; i++) {
    //temp.rows[i] = new IntArray(numColumns);
    for (int j = 0; j < numColumns; j++) {
      (*temp.rows[i])[j] = (*rows[i])[j] + (*rhs.rows[i])[j];
    }
  }
  return temp;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }
  if (rhs.getRows() != 0) {
    s << rhs[rhs.getRows() - 1] << " ]";
  }
  else {
    s << " ]";
  }
  return s;
}
