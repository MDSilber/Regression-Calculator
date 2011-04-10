/*
 * RegressionTester.cpp
 *
 *  Created on: Feb 16, 2011
 *      Author: MasonSilber
 */
#include "regressionCalculator.h"
#include "Matrix.h"
#include "RegressionTester.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
	int numberOfPoints;
	cout << "Welcome to the regression calculator.\nYou can use a linear or a quadratic regression. \nHow many points would you like to enter?\n";
	cin >> numberOfPoints;

	double* xPoints = new double[numberOfPoints];
	double* yPoints = new double[numberOfPoints];

	vector<double> x(5);
	vector<double> y(5);

	cout << "Please input your ordered pairs by separating the x and y coordinates \nwith a space. Then hit enter.\n";
	for(int i = 0; i<5; i++)
	{
		 cin >> xPoints[i]>>yPoints[i];
		 x.push_back(xPoints[i]);
		 y.push_back(yPoints[i]);
	}


	cout<<"Okay, so the points we will be considering are: \n";

	for(int i = 0; i<5;i++)
	{
		cout<< "(" << xPoints[i] << "," << yPoints[i]<<")\n";
	}

	cout << "\nIf you would like a linear regression of your data, type 1. \nIf you'd like a quadratic regression, type 2.\n";
	cout << "If you would like to quit, type 3.\n" << endl;

	int choice;
	cin >> choice;

	if(choice == 1)
	{
		regressionCalculator linear(x,y);
		linear.fitLine();
	}

	if(choice == 2)
	{
		regressionCalculator quadratic(x,y);
		quadratic.fitQuadratic();
	}

	if(choice != 1 && choice != 2)
	{
		if(choice != 3)
		{
			cout << "That is not a valid choice. Please restart program and re-enter data.\n";
		}

		return 1;

	}

	return 0;
}
