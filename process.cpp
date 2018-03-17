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

class Process {
private:
	Process * ptr;

//attributes
	string PID;
	int cpuBurst;
	int priority;
	int arrivalTime;
	int timeLeft;
	int timesRun;
	int howMuchTime;

public:
	thread thrd;

	~Process() //destructor
	{}

// Default Constructor
Process() {
	PID = "NULL";
	thrd; //how to initialize the thread
	cpuBurst =0;
	priority=0;
	arrivalTime=0;
	timeLeft =0;
	timesRun=0;
	howMuchTime=0;
}
    //parameterized constructor
Process(string PID, int CPUburst, int priority, int ArrivalTime, int TimeLeft, int TimesRun, int HowMuchTime) {
		this->PID = PID;
		this->cpuBurst = CPUburst;
		this->priority = priority;
		this->arrivalTime = ArrivalTime;
		this->timeLeft = TimeLeft;
		this->timesRun = TimesRun;
		this->howMuchTime = HowMuchTime;
	}

string getPID() {
	return PID;
}

int getCPUBurst() {
	return cpuBurst;
}

int getPriority() {
	return priority;
}

int getArrivalTime() {
	return arrivalTime;
}

int getTimeLeft() {
	return timeLeft;
}

int getTimesRun() {
	return timesRun;
}

int getHowMuchTime() {
	return howMuchTime;
}

};



