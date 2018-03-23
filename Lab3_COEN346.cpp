// Lab3_COEN346.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
* lab3.cpp
*
*  Created on: Mar 13, 2018
*      Author: Administrateur
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <math.h>
#include <mutex>
#include <windows.h>
#include "ProcessQueue.cpp";

using namespace std;

int currentTime = 0;
bool isDone = false;
bool itemWasInserted = false;
bool lastPass;
bool taskRunning;
bool threadInitialised = false;
int taskEndTime;
int taskGivenTime;
int numOfProcesses;
int arrivedProcesses = 0;
int p = 0;
deque<Process> listOfProcesses;

ProcessQueue process[2] = { ProcessQueue(true), ProcessQueue(false) }; // 2 process queues used

ProcessQueue a = ProcessQueue(true);
ProcessQueue b = ProcessQueue(false);

ofstream output;

void ReadFile(string filename);
int changePriority(Process* a);
int calculateTimeQ(Process* a);
void sheduler(bool activeQueue);
bool sortingFunction(Process* a, Process* b);
bool listSortingFunction(Process a, Process b);
void ProcessInsertion(bool isValid);

mutex processLock;

int main(int argc, char *argv[])
{	

	///reading the input file
	string fileName = "C:/Users/Admin - Jo/Desktop/pbs_input.txt";
	ReadFile(fileName);
	
	processLock.lock();

	while (!isDone) {
		//Check if new stuff need to be added to the queue
		ProcessInsertion(false);
		
		//Go through the scheduler algorithm
		sheduler(process[1].getIsActive());

		// Add +5 to the clock
		currentTime += 5;
	}

	output.close();
	processLock.unlock();
	system("PAUSE");
	return 0;
}

bool listSortingFunction(Process a, Process b) {
	return a.getArrivalTime() < b.getArrivalTime();
}

void DummyTask(int givenTime) {
	processLock.lock();
	int cycles = givenTime/5;
	for (int i = 0; i < cycles; i++) {
		Sleep(5);
		processLock.unlock();
		processLock.lock();
	}
	threadInitialised = false;
	processLock.unlock();
}

void ProcessInsertion(bool isValid) {
	if (isValid || currentTime == listOfProcesses[p].getArrivalTime()) {

			if (!itemWasInserted) {
				itemWasInserted = true;
			}

			if (process[0].getIsActive()) {
				process[1].add(new Process(listOfProcesses[p]));
			}
			else {
				process[0].add(new Process(listOfProcesses[p]));
			}

			cout << "Time " << listOfProcesses[p].getArrivalTime() << ", " << listOfProcesses[p].getPID() << ", Arrived" << endl;
			output << "Time " << listOfProcesses[p].getArrivalTime() << ", " << listOfProcesses[p].getPID() << ", Arrived" << endl;;

			arrivedProcesses++;

			if (p < numOfProcesses - 1) {
				if (currentTime == listOfProcesses[p + 1].getArrivalTime()) {
					p++;
					ProcessInsertion(true);
				}
				else {
					p++;
				}
			}
		}
		
		
}

void ReadFile(string fileName) {
	ifstream InputFile(fileName);

	//Open/output pbs_input.txt file
	output.open("/Users/Admin - Jo/Desktop/pbs_output.txt", std::ios_base::app);
	string pid;
	int arrival;
	int CPU_time;
	int priority;

	if (InputFile.is_open()) {
		InputFile >> numOfProcesses;

		while (InputFile >> pid >> arrival >> CPU_time >> priority) {
			listOfProcesses.push_back(Process(pid, arrival, CPU_time, priority));
		}
		InputFile.close();
	}
	else cout << "file isn't open" << '\n';

	if (listOfProcesses.size() > 0) {
		sort(listOfProcesses.begin(), listOfProcesses.end(), listSortingFunction);
	}

	//Closing the files
	InputFile.close();	
	}

int changePriority(Process* a) {

	int waitingTime = a->getWaitingTime(currentTime);

	int bonus = ceil(10 * waitingTime / (currentTime - a->getArrivalTime()));

	int new_priority = max(100, min(a->getPriority() - bonus + 5, 139));

	cout << "Time " << currentTime << ", " << a->getPID() << ", priority updated to " << new_priority << endl;
	output << "Time " << currentTime << ", " << a->getPID() << ", priority updated to " << new_priority << endl;
	return new_priority;
}

int calculateTimeQ(Process* a) {

	if (a->getPriority() < 100) {
		return ((140 - a->getPriority()) * 20);
	}
	else {
		return ((140 - a->getPriority()) * 5);
	}

}

bool sortingFunction(Process* a, Process* b) {
	return a->getPriority() < b->getPriority();
};

void sheduler(bool activeQueue) {

	if (process[activeQueue].getLength() == 0 && !itemWasInserted) { //Checks whether active is empty + stuff has been added
		return;
	}
	else if (process[activeQueue].getLength() == 0) { //else if Checks whether active is empty
		if (process[!activeQueue].getLength() == 0 && arrivedProcesses == numOfProcesses) { // checks whether non-active is empty
			isDone = true;
			return;
		}
		else {
			process[activeQueue].setIsActive(false);
			process[!activeQueue].setIsActive(true);
			if (process[!activeQueue].getLength() != 0) {
				sort(process[!activeQueue].p.begin(), process[!activeQueue].p.end(), sortingFunction);
				sheduler(process[1].getIsActive());
			}
			
		}
	}
	else { //Active queue is not empty

		if (!taskRunning) { //If no task is currently running, run one
			process[activeQueue].incrTimesRun();
			taskGivenTime = calculateTimeQ(process[activeQueue].getTop());
			int shownGivenTime = taskGivenTime;
			taskEndTime = taskGivenTime + currentTime;
			lastPass = false;

			if (taskEndTime >= process[activeQueue].getTop()->getTimeLeft()+currentTime) {
				taskGivenTime = process[activeQueue].getTop()->getTimeLeft();
				taskEndTime = taskGivenTime + currentTime;
				lastPass = true;
			}

			taskRunning = true;

			if (process[activeQueue].getTop()->getTimesRun() == 1) {
				cout << "Time " << currentTime << ", " << process[activeQueue].getTop()->getPID() << ", " << "Started, Granted " << shownGivenTime << endl;
				output << "Time " << currentTime << ", " << process[activeQueue].getTop()->getPID() << ", " << "Started, Granted " << shownGivenTime << endl;
			}
			else {
				cout << "Time " << currentTime << ", " << process[activeQueue].getTop()->getPID() << ", " << "Resumed, Granted " << shownGivenTime << endl;
				output << "Time " << currentTime << ", " << process[activeQueue].getTop()->getPID() << ", " << "Resumed, Granted " << shownGivenTime << endl;
			}

			//SHOULD RUN TASK HERE

			processLock.unlock();

			process[activeQueue].getTop()->thrd = thread(DummyTask, taskGivenTime);
			process[activeQueue].getTop()->thrd.join();

			processLock.lock();
		}
		else {
			if (taskEndTime <= currentTime) {
				if (!lastPass) {
					cout << "Time " << taskEndTime << ", " << process[activeQueue].getTop()->getPID() << ", Paused" << endl;
					output << "Time " << taskEndTime << ", " << process[activeQueue].getTop()->getPID() << ", Paused" << endl;
					process[activeQueue].getTop()->reduceTimeLeft(taskGivenTime);
				}
				else {
					cout << "Time " << taskEndTime << ", " << process[activeQueue].getTop()->getPID() << ", Terminated" << endl;;
					output << "Time " << taskEndTime << ", " << process[activeQueue].getTop()->getPID() << ", Terminated" << endl;;
				}

				if (process[activeQueue].getTop()->getTimesRun() % 2 == 0 && process[activeQueue].getTop()->getTimesRun() != 0 && !lastPass) {
					process[activeQueue].getTop()->setPriority(changePriority(process[activeQueue].getTop()));
				}

				if (!lastPass) {
					process[!activeQueue].add(process[activeQueue].getTop());
				}

				process[activeQueue].removeTop();
				taskRunning = false;
				sheduler(process[1].getIsActive());
			}
		}
	}

}


