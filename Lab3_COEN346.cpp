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

int currentTime = 0; //Clock
bool isDone = false; // Whether the scheduler is done
bool finalRun; //Whether the currently running process is finishing its task
bool taskRunning; // Whether a task is currently running
int taskEndTime; //The time when the task ends its given time
int taskGivenTime; //The amount of time the current process is given to run
int numOfProcesses; //The total amount of processes that will be run
int arrivedProcesses = 0; //The amount of processes that have arrived
int p = 0; //Current index of the listOfProcesses queue
deque<Process> listOfProcesses; //List of processes read from the input
mutex processLock; //mutex used for mutexing main and process threads

ProcessQueue processQueue[2] = { ProcessQueue(true), ProcessQueue(false) }; // 2 process queues used for active and expired queues

ofstream output; //ofstream for outputting on the output file

void ReadFile(string filename);
int changePriority(Process* a);
int calculateTimeQ(Process* a);
void sheduler(bool activeQueue);
bool sortingFunction(Process* a, Process* b);
bool listSortingFunction(Process a, Process b);
void ProcessInsertion(bool isValid);



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
		sheduler(processQueue[1].getIsActive());

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
	cout << "thread started work shift" << endl;
	int cycles = givenTime/5;
	for (int i = 0; i < cycles; i++) {
		Sleep(5);
		cout << "thread did 5ms work" << endl;
		processLock.unlock();
		Sleep(2);
		processLock.lock();
	}
	cout << "thread ended work shift" << endl;
	processLock.unlock();
}

void ProcessInsertion(bool isValid) {
	if (isValid || currentTime == listOfProcesses[p].getArrivalTime()) {

			if (processQueue[0].getIsActive()) {
				processQueue[1].add(new Process(listOfProcesses[p]));
			}
			else {
				processQueue[0].add(new Process(listOfProcesses[p]));
			}

			cout << "Time " << listOfProcesses[p].getArrivalTime() << ", " << listOfProcesses[p].getPID() << ", Arrived" << endl;
			output << "Time " << listOfProcesses[p].getArrivalTime() << ", " << listOfProcesses[p].getPID() << ", Arrived" << endl;;

			arrivedProcesses++;

			if (p < numOfProcesses - 1) {
					p++;
				if (currentTime == listOfProcesses[p].getArrivalTime()) { //Check whether the next process has the same arrivalTime and the current process
					ProcessInsertion(true);
				}
			}
		}
		
		
}

void ReadFile(string fileName) { //Reads input file, makes process objects from that and sorts the new list of processes
	ifstream InputFile(fileName);

	output.open("/Users/Admin - Jo/Desktop/pbs_output.txt", std::ios_base::app);
	string PID;
	int arrivalTime;
	int cpuBurst;
	int priority;

	if (InputFile.is_open()) {
		InputFile >> numOfProcesses;

		while (InputFile >> PID >> arrivalTime >> cpuBurst >> priority) {
			listOfProcesses.push_back(Process(PID, arrivalTime, cpuBurst, priority));
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

int changePriority(Process* a) { //changed the priority of process a based off the algorithm given

	int waitingTime = a->getWaitingTime(currentTime);

	int bonus = ceil(10 * waitingTime / (currentTime - a->getArrivalTime()));

	int new_priority = max(100, min(a->getPriority() - bonus + 5, 139));

	cout << "Time " << currentTime << ", " << a->getPID() << ", priority updated to " << new_priority << endl;
	output << "Time " << currentTime << ", " << a->getPID() << ", priority updated to " << new_priority << endl;
	return new_priority;
}

int calculateTimeQ(Process* a) { //Finds the allocated time of a process

	if (a->getPriority() < 100) {
		return ((140 - a->getPriority()) * 20);
	}
	else {
		return ((140 - a->getPriority()) * 5);
	}

}

bool sortingFunction(Process* a, Process* b) { //Function specified for std::sort to sort the expired queue
	return a->getPriority() < b->getPriority();
};

void sheduler(bool activeQueue) {

	if (processQueue[activeQueue].getLength() == 0 && arrivedProcesses == 0) { //Checks whether active is empty + stuff has been added
		return;
	}
	else if (processQueue[activeQueue].getLength() == 0) { //else if Checks whether active is empty
		if (processQueue[!activeQueue].getLength() == 0 && arrivedProcesses == numOfProcesses) { // checks whether non-active is empty and whether all processes have arrived
			isDone = true;
			return;
		}
		else { 
		// Active is empty and expired is not => swap active and expired queues and sort inactive only if the inactive queue is not empty
			if (processQueue[!activeQueue].getLength() != 0) {
				processQueue[activeQueue].setIsActive(false);
				processQueue[!activeQueue].setIsActive(true);
				sort(processQueue[!activeQueue].p.begin(), processQueue[!activeQueue].p.end(), sortingFunction);
				sheduler(processQueue[1].getIsActive()); // run a process if you just swapped
			}
			
		}
	}
	else { //Active queue is not empty

		if (!taskRunning) { //If no task is currently running, run one
			processQueue[activeQueue].incrTimesRun();
			taskGivenTime = calculateTimeQ(processQueue[activeQueue].getTop());
			int shownGivenTime = taskGivenTime;
			taskEndTime = taskGivenTime + currentTime;
			finalRun = false;

			if (taskEndTime >= processQueue[activeQueue].getTop()->getTimeLeft()+currentTime) { 
				//If taskEndTime is greater than the end time of the process, make the under the hood runtime the remaining 
				//task length and say it's its last time running
				taskGivenTime = processQueue[activeQueue].getTop()->getTimeLeft();
				taskEndTime = taskGivenTime + currentTime;
				finalRun = true;
			}

			taskRunning = true;

			if (processQueue[activeQueue].getTop()->getTimesRun() == 1) { //If the task was running for the first time, say it has started
				cout << "Time " << currentTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", " << "Started, Granted " << shownGivenTime << endl;
				output << "Time " << currentTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", " << "Started, Granted " << shownGivenTime << endl;
			}
			else {//else, say it resumed
				cout << "Time " << currentTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", " << "Resumed, Granted " << shownGivenTime << endl;
				output << "Time " << currentTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", " << "Resumed, Granted " << shownGivenTime << endl;
			}

			//SHOULD RUN TASK HERE

			processLock.unlock();

			processQueue[activeQueue].getTop()->thrd = thread(DummyTask, taskGivenTime); //Run process thread on dummyTask for length taskGivenTime
			cout << "BETWEEN THREAD" << endl;
			processQueue[activeQueue].getTop()->thrd.join();
			Sleep(2);
			processLock.lock();
		}
		else {
			if (taskEndTime <= currentTime) { //If the task has used all the allocated time or has finished
				if (!finalRun) {//The process has been paused if it wasn't done after its allocated time passed
					cout << "Time " << taskEndTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", Paused" << endl;
					output << "Time " << taskEndTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", Paused" << endl;
					processQueue[activeQueue].getTop()->reduceTimeLeft(taskGivenTime);
				}
				else {//The process is Terminated if it was able to finish after its allocated time passed
					cout << "Time " << taskEndTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", Terminated" << endl;;
					output << "Time " << taskEndTime << ", " << processQueue[activeQueue].getTop()->getPID() << ", Terminated" << endl;;
				}

				if (processQueue[activeQueue].getTop()->getTimesRun() % 2 == 0 && processQueue[activeQueue].getTop()->getTimesRun() != 0 && !finalRun) {
					//if the current task had run twice and it's not its final run
					processQueue[activeQueue].getTop()->setPriority(changePriority(processQueue[activeQueue].getTop()));
				}

				if (!finalRun) {
					//If the current process is not doing its final run
					processQueue[!activeQueue].add(processQueue[activeQueue].getTop());
				}

				processQueue[activeQueue].removeTop();
				taskRunning = false;
				sheduler(processQueue[1].getIsActive());//Start another process after finishing the current one
			}
			if (taskRunning) {
				processLock.unlock();
				Sleep(2);
				processLock.lock();
			}
		}
	}

}


