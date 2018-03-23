/*
* process.cpp
*
*  Created on: Mar 13, 2018
*      Author: Administrateur
*/
#include "stdafx.h"

#include <iostream>
#include <string>
#include <thread>
#include <utility>

using namespace std;

class Process {
private:

	//attributes
	string PID;
	int cpuBurst;
	int priority;
	int arrivalTime;
	int timeLeft;
	int timesRun;
	int timeRun;

public:
	thread thrd;

	~Process() //destructor
	{}
	/*
	// Default Constructor
	Process() {
		PID = "NULL";
		thrd; //how to initialize the thread
		cpuBurst = 0;
		priority = 0;
		arrivalTime = 0;
		timeLeft = 0;
		timesRun = 0;
		timeRun = 0;
	}
	*/

	Process(const Process& obj) 
	{
		PID = obj.PID;
		cpuBurst = obj.cpuBurst;
		priority = obj.priority;
		arrivalTime = obj.arrivalTime;
		timeLeft = obj.timeLeft;
		timesRun = obj.timesRun;
		timeRun = obj.timeRun;
	};

	Process& operator=(const Process& obj) {
		if (this != &obj) {
			PID = obj.PID;
			cpuBurst = obj.cpuBurst;
			priority = obj.priority;
			arrivalTime = obj.arrivalTime;
			timeLeft = obj.timeLeft;
			timesRun = obj.timesRun;
			timeRun = obj.timeRun;
		}
		return *this;
	}

	//parameterized constructor
	Process(std::string PID, int ArrivalTime, int CPUburst, int priority) {
		this->PID = PID;
		this->cpuBurst = CPUburst;
		this->priority = priority;
		this->arrivalTime = ArrivalTime;
		this->timeLeft = CPUburst;
		this->timesRun = 0;
		this->timeRun = 0;
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

	void incrTimesRun() {
		timesRun++;
	}

	void setTimesRun(int timesRun) {
		this->timesRun = timesRun;
	}

	void reduceTimeLeft(int time) {//When you reduce the time left, increase the time runned
		this->timeLeft -= time;
		this->timeRun += time;
	}

	int getWaitingTime(int currentTime) { 
		//Calculate the time waited by substracting the current time from the process's arrival and run time
		return (currentTime - arrivalTime) - timeRun;

	}

	void setPriority(int new_priority) {
		this->priority = new_priority;
	}

};



