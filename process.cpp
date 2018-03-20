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

// Default Constructor
Process() {
	PID = "NULL";
	thrd; //how to initialize the thread
	cpuBurst =0;
	priority=0;
	arrivalTime=0;
	timeLeft =0;
	timesRun=0;
	timeRun=0;
}
    //parameterized constructor
Process(string PID, int CPUburst, int priority, int ArrivalTime) {
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

void reduceTimeLeft(int time) {
	this->timeLeft -= time;
	this->timeRun += time;
}

int getWaitingTime(int currentTime) {

	return (currentTime - this->arrivalTime) - timeRun;

}

void setPriority(int new_priority) {
	this->priority = new_priority;
}

};



