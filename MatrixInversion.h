/*
 * MatrixInversion.h
 *
 *  Created on: Feb 15, 2011
 *      Author: MasonSilber
 */

#ifndef MATRIX_INVERSION_H
#define MATRIX_INVERSION_H

#include "Matrix.h"

/**
This code adapted from:
Press, William H., Teukolsky, Saul A., Vetterling, William T., and Flannery, Brian P.
"Numerical Recipes in C++: The Art of Scientific Computing - Second Edition", Cambridge
University Press, 2002, pgs 49--51.

I adapted the algorithm to work with my Matrix class.  The two functions ludcmp
and lubksb are utility functions used to solve systems of linear equations and
invert square matrices.  Overdetermined systems aren't consider, and the matrices
are all assumed to be square!
*/


// Given an NxN square matrix a, this routine replaces it (a is modified!)
// by the LU decomposition of a row-wise permutation of itself.  a is input.
// indx is an Nx1 column vector, represented as a matrix, that records the
// row permutation effected by the partial pivoting.  d is output as +/- 1
// depending on whether the number of row interchanges was even or odd,
// respectively.  This routine is used in combination with lubksb to solve
// linear equations or invert a matrix.
void ludcmp(Matrix& a, Matrix& indx, double& d);

// Solves the set of N linear equations A*X=B, where A is an NxN square
// matrix, input not as a matrix but rather as its LU decomposition,
// determined by the routine ludcmp.  b is an Nx1 column vector, represented
// as a matrix and returns the solution vector X.  a and indx are not modified
// by this routine and can be left in place for successive calls with different
// right-hand sides b.  This routine takes into account the possibility that b
// will begin with many zero elements, so it is efficient for use in matrix inversion.
void lubksb(const Matrix& a, const Matrix& indx, Matrix& b);


/**

DON'T WORRY ABOUT THE ABOVE 2 FUNCTIONS.  JUST USE THE FOLLOWING
TWO FUNCTIONS TO EITHER SOLVE A SYSTEM OF LINEAR EQUATIONS OR
INVERT A SQUARE MATRIX!

*/


// This solves the set of linear equations: Ax = b, where
// A is an NxN matrix, b is an Nx1 column vector, represented
// as a matrix.  The solution Nx1 column vector x is returned.
Matrix solveLinearSystem(const Matrix& A, const Matrix& b);

// This solves the matrix inversion of an NxN square matrix, and
// is returned.
Matrix invert(const Matrix& A);

#endif
