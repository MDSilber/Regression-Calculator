/*
 * regressionCalculator.h
 *
 *  Created on: Feb 16, 2011
 *      Author: MasonSilber
 */

#ifndef REGRESSIONCALCULATOR_H_
#define REGRESSIONCALCULATOR_H_
#include <vector>

using std::vector;

class regressionCalculator {
public:
	regressionCalculator(vector<double>& x, vector<double>& y);

	regressionCalculator();
	virtual ~regressionCalculator();

	void fitLine(const double* x, const double* y, const int N, double* a, double* b);

	void fitQuadratic(const double* x, const double* y, const int N, double* a, double* b, double* c);

	double sum(vector<double>& x);

	double sumSquares(vector<double>& x);

	double dotProduct(vector<double>& x, vector<double>& y);

	double sumCubes(vector<double>& x);

	double sumDegreeFour(vector<double>& x);

	double xYSquared(vector<double>& x, vector<double>& y);

	void fitLine();

	void fitQuadratic();

	vector<double> getXCoords();

	vector<double> getYCoords();

private:
	vector<double> xCoords;
	vector<double> yCoords;
};

#endif /* REGRESSIONCALCULATOR_H_ */
