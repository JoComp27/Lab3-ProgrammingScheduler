/*
 * lab3.cpp
 *
 *  Created on: Mar 13, 2018
 *      Author: Administrateur
 */

#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <mutex>
#include "ProcessQueue.cpp";

using namespace std;

int currentTime = 0;
bool isDone = false;
bool itemWasInserted = false;
bool lastPass;
bool taskRunning;
int taskEndTime;
int taskGivenTime;
deque<Process> listOfProcesses;

 ProcessQueue a = ProcessQueue(true);
 ProcessQueue b = ProcessQueue(false);

void ReadFile(char* filename);
int changePriority(Process a);
int calculateTimeQ(Process a);
void sheduler();
void ProcessInsertion();

mutex processLock;

int main(int argc, char *argv[])
{
	///reading the input file
   char* fileName = "/Users/Tooba Baig/desktop/pbs_input.txt";
   ReadFile(fileName);

   system("PAUSE");

   processLock.lock();

   while (!isDone) {
	   //Check if new stuff need to be added to the queue
	   ProcessInsertion();
		
	   //Go through the scheduler algorithm
	   sheduler();

	   // Add +100 to the clock
	   currentTime += 100;
   }

}

void DummyTask(int givenTime){
	processLock.lock();
	int cycles = givenTime/100;
	for(int i = 0; i < cycles; i++){
		for(int j = 0; j < 100; j++){
			sleep(1);
		}
		processLock.unlock();
		sleep(2);
		processLock.lock();
	}

	processLock.unlock();
}

void ProcessInsertion() {

	if (currentTime >= listOfProcesses.front().getArrivalTime()) {

		if (!itemWasInserted) {
			itemWasInserted = true;
		}

		if (a.getIsActive()) {
			b.add(listOfProcesses.front());
		}
		else {
			a.add(listOfProcesses.front());
		}

		cout << "Time " << listOfProcesses.front().getArrivalTime() << ", " << listOfProcesses.front().getPID << ", Arrived" << endl;
		listOfProcesses.pop_front();

	}
}

 void ReadFile( char* fileName)
{

	ifstream InputFile (fileName); 
	ofstream output;  

	 //Open/output pbs_input.txt file
   output.open("/Users/Tooba Baig/desktop/pbs_input.txt", std::ios_base::app);

  // Exit program if ifstream could not open file
   if (!InputFile) 
   {
       cout << "File could not be opened" << endl;
       exit(1);
   }

 //Closing the files
   InputFile.close();
   output.close();
}  


int changePriority(Process a){
	//thread t1;
	//int idVar = t1.get_id();
	//int killStatus = kill(idVar, 0);

	int waitingTime = a.getWaitingTime(currentTime);
	int bonus = ceil(10*waitingTime / (currentTime - a.getArrivalTime()));
	int new_priority = max(100, min(a.getPriority() - bonus + 5, 139));
	cout << "Time " << currentTime << ", " << a.getPID() << ", priority updated to " << new_priority;
		return new_priority;

}

int calculateTimeQ(Process a){

	if(a.getPriority() < 100){
		return ((140-a.getPriority()) * 20);
	}
	else{
		return ((140-a.getPriority()) * 5);
	}

}

void sheduler(){

	if (a.getIsActive()) {
		if (a.getLength() == 0 && !itemWasInserted) {
			return;
		}
		else if (a.getLength() == 0) {
			a.setIsActive(false);
			b.setIsActive(true);
			b.sort();
		}
		else { //List A is active and not empty

			if (!taskRunning) { //If no task is currently running, run one
				a.incrTimesRun();
				taskGivenTime = calculateTimeQ(a.getTop());
				taskEndTime = timeGivenTime + currentTime;
				lastPass = false;

				if (taskEndTime > a.getTop().getTimeLeft()) {
					taskEndTime = a.getTop().getTimeLeft() + currentTime;
					lastPass = true;
				}

				taskRunning = true;
			}
			else {
				if (taskEndTime >= currentTime) {
					if (!lastPass) {
						cout << "Time " << taskEndTime << ", " << a.getTop().getPID << ", Paused" << endl;
						a.getTop().reduceTimeLeft(taskGivenTime);
					}
					else {
						cout << "Time " << taskEndTime << ", " << a.getTop().getPID << ", Terminated" << endl;
					}

					if (a.getTop().getTimesRun() == 2) {
						a.getTop().setPriority(changePriority(a.getTop()));
						a.setTimesRun(0);
					}

					if (!lastPass) {
						b.add(a.getTop());
					}
					a.removeTop();
					taskRunning = false;
				}
				else {
					processLock.unlock();
					//runTask
					sleep(2);
					processLock.lock();
				}
			}
		}

	}
	else{
		if(b.getLength() == 0 && !itemWasInserted){
			return;
		}
		else if(b.getLength() == 0){
					b.setIsActive(false);
					a.setIsActive(true);
					a.sort();
				}
		else { //List is not empty

			if (!taskRunning) {
				b.incrTimesRun();

				taskGivenTime = calculateTimeQ(b.getTop());
				taskEndTime = taskGivenTime + currentTime;

				lastPass = false;

				if (taskEndTime > b.getTop().getTimeLeft()) {
					taskEndTime = b.getTop().getTimeLeft() + currentTime;
					lastPass = true;
				}
				
				taskRunning = true;
			}
			else {
				if (taskEndTime >= currentTime) {
					if (lastPass) {
						cout << "Time " << taskEndTime << ", " << b.getTop().getPID << ", Paused" << endl;
						b.getTop().reduceTimeLeft(taskGivenTime);
					}
					else {
						cout << "Time " << taskEndTime << ", " << b.getTop().getPID << ", Terminated" << endl;
					}

					if (b.getTop().getTimesRun() == 2) {
						b.getTop().setPriority(changePriority(b.getTop()));
						b.setTimesRun(0);
					}

					if (!lastPass) {
					a.add(b.getTop());
					}
				b.removeTop();
				taskRunning = false;
				}
				else {
					processLock.unlock();
					//runTask
					sleep(2);
					processLock.lock();
				}
			}
		}
	}

}
