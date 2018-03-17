/*
 * process.cpp
 *
 *  Created on: Mar 13, 2018
 *      Author: Administrateur
 */

#include <iostream>
#include <string>
#include <thread>

using namespace std;

class Process{
public:

	//attributes
	string PID;
	thread_t thrd;
	int CPUburst;
	int priority;
	int ArrivalTime;
	int TimeLeft;
	int TimesRun;
	int HowMuchTime;

	~Process() //destructor
	{}

// Default Constructor
Process()
{
	PID = "NULL";
	thrd; //how to initialize the thread
	CPUburst=0;
	priority=0;
	ArrivalTime=0;
	TimeLeft=0;
	TimesRun=0;
	HowMuchTime=0;
}
    //parameterized constructor
Process(string PID, int CPUburst, int priority, int ArrivalTime, int TimeLeft,
			int TimesRun, int HowMuchTime)
{
		this->PID = PID;
		this->CPUburst = CPUburst;
		this->priority = priority;
		this->ArrivalTime = ArrivalTime;
		this->TimeLeft = TimeLeft;
		this->TimesRun = TimesRun;
		this->HowMuchTime = HowMuchTime;
	}

};



