/*
 * MatrixInversion.cpp
 *
 *  Created on: Feb 15, 2011
 *      Author: MasonSilber
 */

#include "MatrixInversion.h"
#include <iostream>
#include <cmath>


//---------------------------------------------------------------------------
void ludcmp(Matrix& a, Matrix& indx, double& d)
{
  const double TINY = 1.0e-20;
  int i, imax, j, k;
  double big, dum, sum, temp;

  int n = a.numRows();
  Matrix vv(n,1);
  d = 1.0;
  for (i = 0; i < n; i++)
  {
    big = 0.0;
    for (j = 0; j < n; j++)
      if ((temp=fabs(a(i,j))) > big) big = temp;
    if (big == 0.0) exit(-1);  // singular matrix
    vv(i,0) = 1.0/big;
  }

  for (j = 0; j < n; j++)
  {
    for (i = 0; i < j; i++)
    {
      sum = a(i,j);
      for (k = 0; k < i; k++) sum -= a(i,k)*a(k,j);
      a(i,j) = sum;
    }
    big = 0.0;
    for (i = j; i < n; i++)
    {
      sum = a(i,j);
      for (k = 0; k < j; k++) sum -= a(i,k)*a(k,j);
      a(i,j) = sum;
      if ((dum=vv(i,0)*fabs(sum)) >= big)
      {
        big = dum;
        imax = i;
      }
    }
    if (j != imax)
    {
      for (k = 0; k < n; k++)
      {
        dum = a(imax,k);
        a(imax,k) = a(j,k);
        a(j,k) = dum;
      }
      d = -d;
      vv(imax,0) = vv(j,0);
    }
    indx(j,0) = imax;
    if (a(j,j) == 0.0) a(j,j) = TINY;
    if (j != n-1)
    {
      dum = 1.0/(a(j,j));
      for (i = j+1; i < n; i++) a(i,j) *= dum;
    }
  }
}


//---------------------------------------------------------------------------
void lubksb(const Matrix& a, const Matrix& indx, Matrix& b)
{
  int i, ii=0, ip, j;
  double sum;

  int n = a.numRows();
  for (i = 0; i < n; i++)
  {
    ip = static_cast<int>(indx(i,0));
    sum = b(ip,0);
    b(ip,0) = b(i,0);
    if (ii != 0)
      for (j = ii-1; j < i; j++) sum -= a(i,j)*b(j,0);
    else if (sum != 0.0)
      ii = i + 1;
    b(i,0) = sum;
  }

  for (i = n-1; i >= 0; i--)
  {
    sum = b(i,0);
    for (j = i+1; j < n; j++) sum -= a(i,j)*b(j,0);
    b(i,0) = sum/a(i,i);
  }
}


//---------------------------------------------------------------------------
Matrix solveLinearSystem(const Matrix& A, const Matrix& b)
{
  Matrix x;

  // Make sure A is square!
  if (A.numRows() != A.numCols())
  {
    std::cerr << "ERROR!  A must be square matrix!\n";
    return x;
  }

  // Make sure b is a column vector with the same dimensions
  // as A
  if (b.numRows() != A.numRows())
  {
    std::cerr << "ERROR!  b must be a column vector with the same dimensions as square matrix A!\n";
    return x;
  }

  // Make a copy of A since it gets modified
  Matrix Acopy(A);

  const int N = Acopy.numRows();
  Matrix indx(N,1);
  double d;
  ludcmp(Acopy,indx,d);
  x = b;  // x will contain solution
  lubksb(Acopy,indx,x);

  // Return solution column vector
  return x;
}


//---------------------------------------------------------------------------
Matrix invert(const Matrix& A)
{
  Matrix y(A.numRows(), A.numRows(), false);

  // Make sure A is square!
  if (A.numRows() != A.numCols())
  {
    std::cerr << "ERROR!  A must be square matrix!\n";
    return y;
  }

  const int N = A.numRows();

  // Make a copy of A since it gets modified
  Matrix Acopy(A);

 // y.setSize(N,N);
  Matrix col(N,1);
  Matrix indx(N,1);
  double d;
  int i,j;

  ludcmp(Acopy,indx,d);
  for (j = 0; j < N; j++)
  {
    for (i = 0; i < N; i++) col(i,0) = 0.0;
    col(j,0) = 1.0;
    lubksb(Acopy,indx,col);
    for (i = 0; i < N; i++) y(i,j) = col(i,0);
  }

  std::cout.flush();
  // Return result
  return y;
}
