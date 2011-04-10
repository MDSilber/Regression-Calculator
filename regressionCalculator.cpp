/*
 * regressionCalculator.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: MasonSilber
 */

#include "Matrix.h"
#include "regressionCalculator.h"
#include "MatrixInversion.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

regressionCalculator::regressionCalculator(vector<double>& x, vector<double>& y)
{
	xCoords = x;
	yCoords = y;

	cout.flush();
}

regressionCalculator::~regressionCalculator() {
	// TODO Auto-generated destructor stub
}

vector<double> regressionCalculator::getXCoords()
{
	return xCoords;
}

vector<double> regressionCalculator::getYCoords()
{
	return yCoords;
}

void regressionCalculator::fitLine(const double* x, const double* y, const int N, double* a, double* b)
{

}

void regressionCalculator::fitLine()
{
	Matrix a(2,2,false);
	a(0,0) = xCoords.size();
	a(0,1) = sum(xCoords);
	a(1,0) = a(0,1);
	a(1,1) = sumSquares(xCoords);

	Matrix b(2,1,false);
	b(0,0) = sum(yCoords);
	b(1,0) = dotProduct(xCoords,yCoords);

	cout.flush();
	Matrix linearRegression(2,1, false);

	cout.flush();
	linearRegression = invert(a)*b;
	cout.flush();

	cout << "\n\nThe line of best fit is y = " << linearRegression(0,0) << " + " << linearRegression(1,0) << "*x .\n";
}

void regressionCalculator::fitQuadratic(const double* x, const double* y, const int N, double* a, double* b, double* c)
{

}

void regressionCalculator::fitQuadratic()
{
	std::cout.flush();

	Matrix a(3,3,false);
	a(0,0) = xCoords.size();
	a(0,1) = sum(xCoords);
	a(1,0) = a(0,1);
	a(2,0) = sumSquares(xCoords);
	a(1,1) = a(2,0);
	a(0,2) = a(2,0);
	a(2,0) = sumCubes(xCoords);
	a(2,1) = a(2,3);
	a(2,2) = sumDegreeFour(xCoords);

	Matrix b(3,1,false);
	b(0,0) = sum(yCoords);
	b(1,0) = dotProduct(xCoords, yCoords);
	b(2,0) = xYSquared(xCoords, yCoords);

	std::cout.flush();

	Matrix quadraticRegression(3,1,false);
	cout.flush();
	quadraticRegression = invert(a)*b;
	cout.flush();

	cout << "\n\nThe quadratic regression of best fit is y = " << quadraticRegression(0,0) << " + " << quadraticRegression(1,0) << "*x + " << quadraticRegression(2,0) <<"*x^2 .\n";
}

/*This method returns the sum of a set of doubles in a vector.
 *While this would not work for the general case, for this
 *specific program it should be fine
 */
double regressionCalculator::sum(vector<double>& x)
	{
		double sum = 0;
		for(int i = 0; i<x.size(); i++)
		{
			sum += x[i];
		}
		return sum;
	}

/*This method returns the sum of the squares of doubles in a vector.
 *This will be used in calculating the variance
 */
double regressionCalculator::sumSquares(vector<double>& x)
{
	double sumSquares = 0;
	for(int i = 0; i<x.size(); i++)
	{
		sumSquares += pow(static_cast<double>(x[i]),2);
	}
	return sumSquares;
}

double regressionCalculator::dotProduct(vector<double>& x, vector<double>& y)
{
	double dotProduct = 0;
	for(int i = 0; i<x.size(); i++)
	{
		dotProduct += x[i]*y[i];
	}
	return dotProduct;
}

double regressionCalculator::sumCubes(vector<double>& x)
{
	double sumCubes = 0;
	for(int i = 0; i<x.size(); i++)
	{
		sumCubes += pow(static_cast<double>(x[i]),3);
	}
	return sumCubes;
}

double regressionCalculator::sumDegreeFour(vector<double>& x)
{
	double sumFourths = 0;
	for(int i = 0; i<x.size(); i++)
	{
		sumFourths += pow(static_cast<double>(x[i]),4);
	}
	return sumFourths;
}

double regressionCalculator::xYSquared(vector<double>& x, vector<double>& y)
{
	double xYSquared = 0;
	for(int i = 0; i<x.size(); i++)
	{
		xYSquared += x[i] * pow(static_cast<double>(y[i]),2);
	}
	return xYSquared;
}
