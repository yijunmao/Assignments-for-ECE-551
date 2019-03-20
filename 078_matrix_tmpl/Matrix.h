#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
//using namespace std;

//YOUR CODE GOES HERE!
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(std::vector<std::vector<T> >()) {}

  Matrix(int r, int c) :
      numRows(r),
      numColumns(c),
      // vector<T>(c, T()) you have to write T() here because it's an object while T is just a type
      rows(std::vector<std::vector<T> >(r, std::vector<T>(c, T()))) {
    //std::vector<std::vector<T> > bigVector;
    /*for (int i = 0; i < r; i++) {
      std::vector<T> innerVector(c);
      rows.push_back(innerVector);
      }*/
  }
  /*for (int i = 0; i < numRows; i++) {
      rows[i] = vector<T>(c, 0);
    }*/

  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = rhs.rows;
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  std::vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows) {
      return 0;
    }
    if (numColumns != rhs.numColumns) {
      return 0;
    }
    for (int i = 0; i < rhs.numRows; i++) {
      for (int j = 0; j < rhs.numColumns; j++) {
        if (rows[i][j] != rhs.rows[i][j]) {
          return 0;
        }
      }
    }
    return 1;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
    Matrix<T> res(rhs.numRows, rhs.numColumns);
    for (int i = 0; i < rhs.numRows; i++) {
      for (int j = 0; j < rhs.numColumns; j++) {
        res.rows[i][j] = rows[i][j] + rhs.rows[i][j];  //
      }
      //vector1<T> + vector2<T>
    }
    return res;
  }

  template<typename K>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<K> & rhs);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.numRows == 0) {
    s << "[ ]";
  }
  else {
    s << "[ ";
    for (int i = 0; i < rhs.numRows; i++) {
      s << "{";
      for (int j = 0; j < rhs.numColumns - 1; j++) {
        s << rhs.rows[i][j] << ", ";
      }
      s << rhs.rows[i][rhs.numColumns - 1] << "}";
      if (i != rhs.numRows - 1) {
        s << "," << std::endl;
      }
      else {
        s << " ]";
      }
    }
  }
  return s;
}

#endif
