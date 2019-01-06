/*******************************************************************************************************************************************
Filename:			ass2.cpp
Version:			1.0
Author:				Kevin Lai
Student No:			040812704
Course Name/Number:	Numerical Computing
Lab Sect:			304
Assignment #:		2
Assignment name:	Linear Regression Fit to Data
Due Date:			November 11 2018
Submission Date:	November 11 2018
Professor:			Andrew Tyler
Purpose:			Fit data using linear regression least squares method for both a Linear function and a Power law function.
********************************************************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <string.h>
#include <fstream>
#include <cmath>
using namespace std;
 
void readFile(vector<vector<float>> &dataSet, int& counter, bool isPower);
void interExpoMenu(vector<vector<float>> &dataSet, int counter, bool isPower);
float sumOfX(vector<vector<float>> & dataSet, int counter);
float sumOfProductXY(vector<vector<float>> & dataSet, int counter);
float sumOfSquaredX(vector<vector<float>> & dataSet, int counter);
float delta(vector<vector<float>> & dataSet, int counter);
float m(vector<vector<float>> & dataSet, int counter);
float c(vector<vector<float>> & dataSet, int counter);

/*******************************************************************************************************************************************
Function name: main
Purpose: menu with 3 options (1 : Linear Fit , 2: Power Law Fit, 3: Quit). If user choose 1 then evaluate least squares linear regression
								with linear fit. otherwise 2 if evaluate with power law fit and 3 to quit.
Function In Parameters: none
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
int main()
{
	int choice = 0, counter;
	
	cout << "LEAST_SQUARES LINEAR REGRESSION" << endl;

	do
	{
		vector<vector<float>> dataSet;
		counter = 0;
		cout << "MENU\n 1. Linear Fit\n 2. Power Law Fit\n 3. Quit\n";

		while (!(cin >> choice) || choice < 1 || choice > 3)
		{
			cout << "invalid choice\n";
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}


		switch (choice)
		{
			case 1: 
				readFile(dataSet, counter, false);
				cout << fixed;
				cout << setprecision(2);
				cout << "There are " << counter << " records." << endl;
				cout << "y = " << m(dataSet, counter) << "*x + " << c(dataSet, counter) << endl;
				interExpoMenu(dataSet, counter, false);
				break;
			case 2: 
				readFile(dataSet, counter, true);
				cout << fixed;
				cout << setprecision(2);
				cout << "There are " << counter << " records." << endl;
				cout << "y = " << exp(c(dataSet, counter)) << "*x^" << m(dataSet, counter) << endl;
				interExpoMenu(dataSet, counter, true);
				break;

			case 3: cout << "Goodbye!"<< endl;
				break;
		}
	}
		while (choice != 3);

	return 0;
}

/*******************************************************************************************************************************************
Function name: sumOfX
Purpose: calculate sum of all the X's
Function In Parameters: vector<vector<float>> & dataSet, int counter
Function Out Parameters: sum(float)
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
float sumOfX(vector<vector<float>> & dataSet, int counter)
{
	float sum = 0;
	for (int i = 0; i < counter; i++)
	{
		sum += dataSet[i][0];
	}
	return sum;
}

/*******************************************************************************************************************************************
Function name: sumOfY
Purpose: calculate sum of all the Y's
Function In Parameters: vector<vector<float>> & dataSet, int counter
Function Out Parameters: sum(float)
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
float sumOfY(vector<vector<float>> & dataSet, int counter)
{
	float sum = 0;
	for (int i = 0; i < counter; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if(j%2 == 1)
			sum += dataSet[i][j];
		}
	}
	return sum;
}

/*******************************************************************************************************************************************
Function name: sumOfProductXY
Purpose: calculate sum of all the Product of X's and Y's
Function In Parameters: vector<vector<float>> & dataSet, int counter
Function Out Parameters: sum(float)
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
float sumOfProductXY(vector<vector<float>> & dataSet, int counter)
{
	float product = 1;
	float sum=0;
	for (int i = 0; i < counter; i++)
	{
		product = 1;
		for (int j = 0; j < 2; j++)
		{
			product *= dataSet[i][j];
		}
		sum += product;
	}
	return sum;
}

/*******************************************************************************************************************************************
Function name: sumOfSquaredX
Purpose: calculate sum of all the squared X's
Function In Parameters: vector<vector<float>> & dataSet, int counter
Function Out Parameters: sum(float)
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
float sumOfSquaredX(vector<vector<float>> & dataSet, int counter)
{
	float sum = 0;
	for (int i = 0; i < counter; i++)
	{		
		sum += pow(dataSet[i][0],2);
	}
	return sum;
}

/*****************************************************************************************************************************
Function Name: delta
Purpose: calculate the delta using formula delta = counter*Sxx - (Sx)^2
In parameters: vector<vector<float>> & dataSet, int counter
Out parameters: delta(float)
Version: 1.0
Author: Kevin Lai
*****************************************************************************************************************************/
float delta(vector<vector<float>> & dataSet, int counter)
{
	float delta = counter*sumOfSquaredX(dataSet, counter) - pow(sumOfX(dataSet, counter), 2);
	return delta;
}

/*******************************************************************************************************************************************
Function name: m
Purpose: to calculate the slope m using formula m = (SSxy - SxSy) / delta.
Function In Parameters: vector<vector<float>> & dataSet, int counter
Function Out Parameters: m(float)
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
float m(vector<vector<float>> & dataSet, int counter)
{
	float m = (counter*sumOfProductXY(dataSet, counter) - (sumOfX(dataSet, counter)*sumOfY(dataSet, counter))) / delta(dataSet, counter);
	return m;
}

/*******************************************************************************************************************************************
Function name: c
Purpose: to calculate the constant c using formula c = (SxxSy - SxSxy) / delta.
Function In Parameters: vector<vector<float>> & dataSet, int counter
Function Out Parameters: c(float)
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
float c(vector<vector<float>> & dataSet, int counter)
{
	float c = (sumOfSquaredX(dataSet, counter)*sumOfY(dataSet, counter) - (sumOfX(dataSet, counter) * sumOfProductXY(dataSet, counter))) / delta(dataSet, counter);
	return c;
}

/*******************************************************************************************************************************************
Function name: interExpoMenu
Purpose: offer the user the option of interpolating/ extrapolating the databy including the (1960, 316.5) offsets to the formula you 
		 calculate. Depending on boolean passed in parameter to indicate power fit or linear fit.
Function In Parameters: vector<vector<float>> &dataSet, int counter, bool isPower
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
void interExpoMenu(vector<vector<float>> &dataSet, int counter, bool isPower)
{
	int choice;
	float year;
	do
	{
		cout << "MENU\n 1. Interpolate/Extrapolate\n 2. Main Menu\n";
		
		while (!(cin >> choice) || choice < 1 || choice > 2)
		{
			cout << "invalid choice\n";
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
		}


		switch (choice)
		{
			case 1:
				cout << "Please enter the year to interpolate/extrapolate to: ";
				cin >> year;
				if(isPower)
				cout << "The power law interpolated/extrapolated CO2 level in the year " << setprecision(1) << year << setprecision(2) << " is " << (exp(c(dataSet, counter)) * pow((year-1960), m(dataSet, counter))) + 316.5 << endl;
				else
					cout << "The power law interpolated/extrapolated CO2 level in the year "<< setprecision(1) << year << setprecision(2) << " is " << (m(dataSet, counter) * (year - 1960) + c(dataSet, counter)) + 316.5 << endl;
				break;
			case 2:
				
				break;
		}
	} while (choice != 2);
}

/*******************************************************************************************************************************************
Function name: readFile
Purpose: read in file and store all the values in a 2 dimensional vector of floats, if power law fit then store all the values as logs.
Function In Parameters: vector<vector<float>> & dataSet, int &counter, bool isPower
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
void readFile(vector<vector<float>> & dataSet, int &counter, bool isPower)
{
	string line;
	string fileName;
	ifstream inFile;
	float tempFloat;
	cout << "Please enter the name of the file to open: ";
	cin >> fileName;
	inFile.open(fileName, fstream::in); /*open file for reading*/

	if (inFile.is_open()) 
	{
		while (getline(inFile, line))
		{
			counter++; /*count number of lines in our file*/
		}

		inFile.clear();
		inFile.seekg(0, ios::beg);

		for (int i = 0; i < counter; i++)
		{
			dataSet.emplace_back(0);
			for (int j = 0; j < 2; j++)
			{
				inFile >> tempFloat;
				if (isPower)
					dataSet[i].emplace_back(log(tempFloat));  /*Power Law so we get the log of the Y's and X's*/
				else
					dataSet[i].emplace_back(tempFloat);
			}
		}
	}
	inFile.close();
}