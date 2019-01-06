/*******************************************************************************************************************************************
Filename:			ass1.cpp
Version:			1.0
Author:				Kevin Lai
Student No:			040812704
Course Name/Number:	Numerical Computing
Lab Sect:			304
Assignment #:		1
Assignment name:	Catenary Function
Due Date:			October 14 2018
Submission Date:	October 13 2018
Professor:			Andrew Tyler
Purpose:			Investigate a Maclaurin series approximation to the Catenary function.
********************************************************************************************************************************************/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

/*******************************************************************************************************************************************
Function name: main
Purpose: menu with 2 options (1 : Evaluate the function , 2: Quit). If user chooses 1 then the function will evaluate the cantenary
		 function with the values given from the user.
Function In Parameters: none
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
int main()
{
	int choice = 0;
	do
	{
		cout << "**********************************\n\tCatenary Series\n1. Evaluate the function\n2. Quit\n**********************************\n";

		while (!(cin >> choice) || choice < 1 || choice > 2)
		{
			cout << "invalid choice\n";
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}

		// does the calculation for the cantenary function(get all input from user to do calculations) highest power of X, low X, high X and scale
		if (choice == 1)
		{
			int power = 0;  /*holds the highest power of X in the catenary series*/
			double lowX = 0.0;  /*lowX range(-10.0 to 0.0)*/
			double highX = 0.0; /*highX range(0.0 to 10.0)*/
			double scale = 0.0; /*scale factor (0.0 to 10.0 the higher the number the more its magnifying the curve )*/
			double sumSeries = 0.0;  /*add all the terms in the series together*/
			double x = 0.0;  /*current X value being evaluated in the catenary series*/
			double truncatedTerm = 0.0;  /*Term that comes after the highest power of X term eg. power is 8 so trunc is 10*/
			double exactValue = 0.0;  /*Exact value of the cantenary series using math library */

			cout << "\tEVALUATING THE CATENARY SERIES APPROXIMATION\n\n";

			cout << "Please enter the highest power of x in the catenary series(0, 2, 4, 6, 8, or 10) : ";
			while (!(cin >> power) || power % 2 == 1 || (power < 0 || power > 10))
			{
				cout << "invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits <streamsize> ::max(), '\n');
			}

			cout << endl << "\tCHOOSE THE RANGE OF EVALUATION - low x to high x" << endl;

			cout << "Please enter low x - in the range -10.0 to 0.0: ";
			while (!(cin >> lowX) || lowX < -10.0 || lowX > 0.0)
			{
				cout << "invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits <streamsize> ::max(), '\n');
			}

			cout << "Please enter high x - in the range 0.0 to +10.0: ";
			while (!(cin >> highX) || highX < 0 || highX > 10)
			{
				cout << "invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits <streamsize> ::max(), '\n');
			}

			cout << endl << "Please enter the scale factor the range 0.0 to +10.0: ";
			while (!(cin >> scale) || scale < 0 || scale > 10)
			{
				cout << "invalid input \n";
				cin.clear();
				cin.ignore(numeric_limits <streamsize> ::max(), '\n');
			}

			cout << fixed;
			cout.precision(6);
			cout << endl << "CATENARY SERIES TO x^" << power << " from x = " << lowX << " to x = " << highX << endl;

			double increment = (highX - lowX) / 10.0;  /*increment between each X value in the catenary series*/

			cout << scientific;  /*setting scientific mode*/

			cout << setw(6) << " x" << setw(19) << "Series" << setw(16) << "Exact" << setw(20) << "Exact % Error" << setw(16) << "Trunc. % Error" << endl;
			for (int i = 0; i <= 10; i++)
			{
				sumSeries = 0.0;
				x = lowX + (increment * i);

				/*depending on the power the user selects for the highest term in the cantenary series, the switch case statement will produce the sum of the series. and truncated term*/

				switch (power)
				{
					case 10:
						sumSeries += scale * ((x * x * x * x * x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10)));

						if (power == 10)
							truncatedTerm = scale * ((x * x * x * x * x * x * x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale * scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12)));
					case 8:
						sumSeries += scale * ((x * x * x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6 * 7 * 8)));

						if (power == 8)
							truncatedTerm = scale * ((x * x * x * x * x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10)));
					case 6:
						sumSeries += scale * ((x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6)));

						if (power == 6)
							truncatedTerm = scale * ((x * x * x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6 * 7 * 8)));
					case 4:
						sumSeries += scale * ((x * x * x * x) / ((scale * scale * scale * scale) * (1 * 2 * 3 * 4)));

						if (power == 4)
							truncatedTerm = scale * ((x * x * x * x * x * x) / ((scale * scale * scale * scale * scale * scale) * (1 * 2 * 3 * 4 * 5 * 6)));
					case 2:
						sumSeries += scale * ((x * x) / ((scale * scale) * (1 * 2)));

						if (power == 2)
							truncatedTerm = scale * ((x * x * x * x) / ((scale * scale * scale * scale) * (1 * 2 * 3 * 4)));
					case 0:
						sumSeries += scale;

						if (power == 0)
							truncatedTerm = scale * ((x * x) / ((scale * scale) * (1 * 2)));
						break;
				}

				exactValue = (scale * (exp(x / scale) + exp(-x / scale)) / 2);  /*get exact value of the series using math library */
				cout << setprecision(3) << showpos << x << "\t" << setprecision(5) << noshowpos << sumSeries << "\t" << exactValue << "\t" << 100 * (exactValue - sumSeries) / exactValue << "\t" << 100 * truncatedTerm / sumSeries << endl;
			}
			cout << endl;
		}
	} while (choice != 2); /*keep user in loop until they choose 2 to quit*/

	return 0;
}
