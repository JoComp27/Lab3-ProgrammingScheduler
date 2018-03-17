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
#include "ProcessQueue.cpp";

using namespace std;

int currentActiveQueue = 0;
bool isDone = false;

void ReadFile(char* filename);
int changePriority(Process a);
int calculateTimeQ(Process a);
void sheduler(ProcessQueue* a, ProcessQueue* b);


int main(int argc, char *argv[])
{
	///reading the input file
   char* fileName = "/Users/Tooba Baig/desktop/pbs_input.txt";
   ReadFile(fileName);
   system("PAUSE");

   ProcessQueue a = ProcessQueue(true);
   ProcessQueue b = ProcessQueue(false);

   while (!isDone) {
	   //Check if new stuff need to be added to the queue

	   //Go through the scheduler algorithm

	   // Add +100 to the clock
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
	thread t1;
	int idVar = t1.get_id();
	int killStatus = kill(idVar, 0);
}

int calculateTimeQ(Process a){

	if(a.priority < 100){
		return ((140-a.priority) * 20);
	}
	else{
		return ((140-a.priority) * 5);
	}

}

void sheduler(ProcessQueue* a, ProcessQueue* b){

	if(a->getIsActive()){
		if(a->getLength() == 0 && !itemWasInserted){
			return;
		}
		else if(a->getLength() == 0){
			a->setIsActive(false);
			b->setIsActive(true);
			b->sort();
		}
		else{

		}

		if()

}
	else{
		if(b->getLength() == 0 && !itemWasInserted){
			return;
		}
		else if(b->getLength() == 0){
					b->setIsActive(false);
					a->setIsActive(true);
					a->sort();
				}
		else{

		}

	}

}


for(int i =0 ; i < waitingtime.size() ; ++i)
{
	waitingtime[i+1] += waitingtime[i]
}
