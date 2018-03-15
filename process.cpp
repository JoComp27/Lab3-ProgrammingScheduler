/*
 * process.cpp
 *
 *  Created on: Mar 13, 2018
 *      Author: Administrateur
 */

#include <iostream>
#include <string>

using namespace std;

class Process{
public:
	string PID;
	int CPUburst;
	int priority;
	int ArrivalTime;
	int TimeLeft;
	int TimesRun;
	int HowMuchTime;

	Process(string PID, int CPUburst, int priority, int ArrivalTime, int TimeLeft,
			int TimesRun, int HowMuchTime){
		this->PID = PID;
		this->CPUburst = CPUburst;
		this->priority = priority;
		this->ArrivalTime = ArrivalTime;
		this->TimeLeft = TimeLeft;
		this->TimesRun = TimesRun;
		this->HowMuchTime = HowMuchTime;
	}



};



