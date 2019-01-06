/*******************************************************************************************************************************************
Filename:			ass3.cpp
Version:			1.0
Author:				Kevin Lai
Student No:			040812704
Course Name/Number:	Numerical Computing
Lab Sect:			304
Assignment #:		3
Assignment name:	Martian Lander
Due Date:			December 02 2018
Submission Date:	December 02 2018
Professor:			Andrew Tyler
Purpose:			Solve Ordinary differential Equations (ODEs) in real-time for a planetary lander flight simulator.
********************************************************************************************************************************************/
#include <algorithm>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

#define SECONDS_PER_MINUTE 60

void simulation();
void displayRecords();

class Records
{
	string name;
	int bounce;
	int minutes;
	int seconds;
	int milliseconds;

public :
	/*default constructor*/
	Records(string str, int b, int m, int s, int mi) :name(str), bounce(b), minutes(m), seconds(s), milliseconds(mi) {};
	
	/*function is a comparator (compares the numbers of bounces and times)*/
	bool operator < (const Records & a)
	{
		if (this->bounce - a.bounce == 0)
		{
			if (this->minutes - a.minutes == 0)
			{
				if (this->seconds - a.seconds == 0)
				{
					if (this->milliseconds - a.milliseconds == 0) return true;
					else return (this->milliseconds < a.milliseconds);
				}
				else return (this->seconds < a.seconds);
			}
			else return (this->minutes < a.minutes);
		}
		else return (this->bounce < a.bounce);
	}

	/*function to display the members of this class in a proper format*/
	void display()
	{
		cout << name << "\t" << setw(20) << bounce << setw(16) << minutes << setw(16) << seconds << setw(19) << milliseconds << endl;
	}
};

/*******************************************************************************************************************************************
Function name: main
Purpose: menu with 2 options (1 : Run Simulation , 2: Quit And Show Highscores. If user choose 1 then run the planetary lander flight 
		 simulator otherwise 2 to display highscores sorted by the best to worse then quit.
Function In Parameters: none
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
int main()
{	
	int choice = 0;

	cout << "Martian Lander" << endl;
	cout << "--------------" << endl;

	do
	{
		cout << "MENU\n 1. Run Simulation\n 2. Quit And Show Highscores\n";

		cin >> choice;

		switch (choice)
		{
			case 1:
				simulation();
				break;
			case 2:
				displayRecords();
				break;
		}
	} while (choice != 2);

	return 0;
}

/*******************************************************************************************************************************************
Function name: displayRecords
Purpose: Read in file and store all variables to create objects of Records to insert into a vector. Sort the Records
		 with the least amount of bounces and times to appear first. Display to console all the records from best to worse.
Function In Parameters: none
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
void displayRecords()
{
	system("CLS"); /*clears the console*/
	vector<Records> records; /*vector to hold all records*/
	ifstream inFile; /*stream for reading*/
	string name; /*hold names that are read from the file*/
	char c; /*character used to fetch '\n' so we are able to check for EOF*/
	int bounce; /*hold bounce values that are read from the file*/
	int minutes = 0.0; /*hold minute values that are read from the file*/
	int seconds = 0.0; /*hold second values that are read from the file*/
	int milliseconds = 0.0; /*hold millisecond values that are read from file*/
	inFile.open("records.out", fstream::in); /*set the stream for reading mode*/

	/*check to see if file opened properly*/
	if (inFile.is_open())
	{
		while (1)
		{
			inFile.get(c);
			if (c != '\n')
			{
				if (inFile.eof())
					break;
				inFile.putback(c);
			}
			else
			{
				inFile.get(c);
				if (inFile.eof())
					break;
				else
					inFile.putback(c);
			}
				inFile >> name >> bounce >> minutes >> seconds >> milliseconds; /*save all values read from file to variables.*/
				records.emplace_back(name, bounce, minutes, seconds, milliseconds); /*insert record object into vector*/
		}
		if (records.size() == 0)
		{
			cout << "There are no Records to display"<< endl;
		}
		else
		{

			cout << setw(50) << "HighScores" << endl;
			cout << "--------------------------------------------------------------------------------------" << endl;

			/*sort records with the least amount of bounces and times to appear first*/
			sort(records.begin(), records.end());

			cout << "Name\t\t\tBounces\t\tMinutes\t\tSeconds\t\tMilliseconds" << endl;

			/*display to console all the records from best to worse*/
			for (int i = 0; i < (signed int) records.size(); i++)
			{
				records[i].display();
			}
		}
	}
	else
	{
		cout << "There are no records to display"<< endl;
	}

	inFile.close(); /*close file stream */
}

/*******************************************************************************************************************************************
Function name: simulation
Purpose: Function implements a loop to calculate the velocity, time and distance of module from the ground using heun's method. 
		 Values are updated each iteration and displayed to the console. 
Function In Parameters: none
Function Out Parameters: none
Version: 1.0
Author/Student Name: Kevin Lai
*******************************************************************************************************************************************/
void simulation()
{
	string name; /*name of user that is playing the simulation*/
	double x = 1000; /*height of module*/
	double b = 0.0; /*braking*/
	double g = 3.7; /*gravity*/
	double c = 0.13; /*deceleration caused by atmospheric drag*/
	double v = 0.0;   /*velocity*/
	double a = 8.3;  /*acceleration*/
	double vmax = 46; /*velocityMax*/
	double previousChangeOfVelocity = 0.0; /* holds differential equation for previousV*/
	double changeOfVelocity = 0.0; /*holds differential equation for velocity*/
	double burnReserve = 100; /*amount of fuel*/
	double timeElasped = 0.0; /*time from the start of simulation until the end*/
	double deltaTime = 0.0; /*time between each loop iteration*/
	double currentTime = 0.0; /*current time that gets updated at beginning of each iteration*/
	bool startingDescent = true; /*prints the startingDescent header if W or E hasn't been pressed*/
	bool hasBoost = true; /*boolean to check if there is still fuel*/
	double previousV = 0.0; /*variable to save the previous velocity*/
	double previousTime = GetCurrentTime(); /*previous time is updated at the end of each loop by assigning currentTime to it*/
	int bounce = 0; /*keep track of number of time module bounces off the ground*/
	int key = 0; /*saves the key that is pressed*/
	int oldKey = 0; /*holds the old key incase keys that aren't (W,E) are pressed*/

	for (;;)
	{
		currentTime = GetCurrentTime();
		deltaTime = currentTime - previousTime;
		timeElasped += deltaTime;

			previousChangeOfVelocity = g - c*(v + a*(pow(v / vmax, 3))) - b; /*differential equation for change of velocity over time*/
			previousV = v + (previousChangeOfVelocity * (deltaTime / CLOCKS_PER_SEC)); /*calculate velocity */
			changeOfVelocity = g - c*(previousV + a*(pow(previousV / vmax, 3))) - b; /*recalculate changeOfVelocity using PreviousV*/
			v = v + (previousChangeOfVelocity + changeOfVelocity) / 2 * (deltaTime / CLOCKS_PER_SEC);  /*using Heun's method to get more precise velocity*/
			x = x - ((previousV + v) / 2) * (deltaTime / CLOCKS_PER_SEC); /*calculation for new x position*/

			/*condition to check for a smooth landing*/
			if (x >= 0 && x < 1 && v >= 0 && v < 1)
			{
				cout << "Enter a name: ";
				cin >> name;

				ofstream offFile; /*outFile stream*/
				offFile.open("records.out", ofstream::app); /*set stream to append simulation records*/

				offFile << name << " "<< bounce <<" " << ((int) timeElasped / CLOCKS_PER_SEC / SECONDS_PER_MINUTE) << " " << ((int) timeElasped / CLOCKS_PER_SEC % SECONDS_PER_MINUTE) << " "<< (int) timeElasped%CLOCKS_PER_SEC << endl;
				system("CLS"); /*clears the console*/
				offFile.close(); /*close ofstream*/
				break;
			}

			/*condition to check for bounce*/
			if (x <= 0)
			{
				/*increment bounce if velocity is greater then 1 when hitting the ground*/
				if (v > 1)
				{
					v *= -1;
					bounce++;
				}
			}

			/*check to see if a key was hit*/
			if (_kbhit())
			{
				key = _getch();
				if (key == 'q')
					break;
				else if (key == 'w')
				{
					if (hasBoost)
						b += 1;
					oldKey = key;
					startingDescent = false; /*set to false so it wont print the startDescent header anymore*/
				}
				else if (key == 'e')
				{
					if (b > 0)
						b -= 1;
					oldKey = key;
					startingDescent = false; /*set to false so it wont print the startDescent header anymore*/
				}
				else
				{
					key = oldKey; /*set key back to previous key that was clicked either w or e (incase other keys get pressed)*/
				}
			}

			if (hasBoost)
			{
				if (burnReserve <= 0)
				{
					hasBoost = false;
					burnReserve = 0;
					b = 0;
				}
				else if (b > 0 && burnReserve>0)
				{
					if (key == 'w')
					{
						cout << "W was pressed - increase burn: ";
					}
					else if (key == 'e')
					{
						cout << "E was pressed - reduce burn: ";
					}
					burnReserve -= (b*(deltaTime / CLOCKS_PER_SEC)); /*decrement the burnReserve based on forumula*/
				}
				else if (key == 'e')
				{
					cout << "E was pressed - reduce burn: ";
				}
			}

			/*Print out to the console*/
		if (startingDescent)
			cout << "******************************** STARTING DESCENT ***************************************" << endl;
		cout << ": BURN = " << setprecision(3) << fixed << b << "; BURN RESERVE = " << burnReserve << endl;
		cout << "MINUTE = " << ((int) timeElasped / CLOCKS_PER_SEC / SECONDS_PER_MINUTE) << "; SECOND = " << ((int) timeElasped / CLOCKS_PER_SEC % SECONDS_PER_MINUTE) << "; MILLISECOND = " << (int) timeElasped%CLOCKS_PER_SEC << endl;
		cout << "SPEED OF DESCENT = " << v << "m/s" << endl;
		cout << "HEIGHT ABOVE MARTIAN SURFACE = " << x << "meters" << endl;
		cout << "NUMBER OF BOUNCES = " << bounce << endl;

		Sleep(50);
		system("CLS"); /*clears the console*/
		previousTime = currentTime; /*update Previous Time and make it equal to Current Time which is time measured at the beginning of the iteration*/
	}// end for loop
}
