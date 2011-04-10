/*
 * Matrix.h
 *
 *  Created on: Feb 10, 2011
 *      Author: MasonSilber
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
  // Let's declare some friend functions to define the basic
  // arithmetic on a Matrix

  // a + b
  friend Matrix operator+(const Matrix& a, const Matrix& b);
  // a - b
  friend Matrix operator-(const Matrix& a, const Matrix& b);
  // Matrix scaling: a*s, for Matrix a
  friend Matrix operator*(const Matrix& a, const double s);
  // Matrix scaling: s*a, for Matrix a
  friend Matrix operator*(const double s, const Matrix& a);

  // Matrix multiplication: a_[mxn] * b_[nxk] = c_[mxk]
  friend Matrix operator*(const Matrix&a, const Matrix&b);

  // Overload the stream operator so we can use cout with our Matrix class
  friend std::ostream& operator<<(std::ostream& output, const Matrix& a);

public:
  // Construct with the height and width of the matrix, with default values
  // of zeros
  Matrix(const unsigned int numRows = 0, const unsigned int numCols = 0, bool askValues = false);

  // Cleanup the memory in the destructor
  ~Matrix();

  // A copy constructor reallocates when necessary, and then copies in the
  // data from rhs
  Matrix(const Matrix& rhs);

  // The assignment operator does the same as the copy constructor, but
  // then returns a reference to "me"
  Matrix& operator=(const Matrix& rhs);

  void setMatrix(Matrix m);

  void setMatrix(int row, int col, double value);

  inline double** getMatrix() const
  {
	return mData;
  }

  // Retrieve the height (number of rows) in the matrix
  inline int numRows() const
  {
    return mNumRows;
  }

  // Retrieve the width (number of columns) in the matrix
  inline int numCols() const
  {
    return mNumCols;
  }

  void getValue(int row, int column);

  void setValue(int row, int column);

  void print();

  // Compute and return the transpose of this Matrix
  Matrix transpose() const;

  // Overload the () operator to get access to the data in a natural
  // (MATLAB-like) way, but note that it is still 0-based!
  //
  // Note that we return a reference to the entry in the array to allow
  // the user to both SET and GET values using this operator.
  //
  // In terms of error-checking, we don't check the correct bounds on the row
  // and column.  You need to be sure to use this carefully or you'll
  // get a memory error.  We do this so that the function can be used
  // efficiently and we don't keep calling lots of if conditionals
  // each time this is called.  We also don't check if the mData pointer
  // is NULL for the same reason, so make sure you allocate correctly before
  // using this.
  //
  double& operator()(const unsigned int row, const unsigned int col);

  const double& operator()(const unsigned int row, const unsigned int col) const;

  // Overload the += operator (this is done as a method and not an external
  // friend b/c it's something I'm doing to "myself", and then I return
  // "myself"
  //
  // a += b ---> a = a + b, where "I" am "a"
  Matrix& operator+=(const Matrix& a);
  //
  // a -= b ---> a = a - b
  Matrix& operator-=(const Matrix& a);

  void setSize(const unsigned int newRows, const unsigned int newCols);

private:
  // The actual matrix data is represented as a dynamically-allocated
  // 2D array
  double** mData;

  // The dimensions of the matrix are unsigned integers (since non-zero
  // values make no sense).
  unsigned int mNumRows;
  unsigned int mNumCols;
  bool askValues;
};



#endif
