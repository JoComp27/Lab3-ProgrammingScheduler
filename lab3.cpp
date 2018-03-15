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
#include "process.cpp";

using namespace std;

Process[] a;
Process[] b;

int currentActiveQueue = 0;

int main(){
	void resumeprocess();
	void pauseprocess();
	ifstream infile;
	infile.open("")
	string readfile( string )
 process scheduler()
  int waitingtime[];

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

void sheduler(){

	if(a.getActive()){
		if(a.getSize() == 0 && !itemWasInserted){
			return;
		}
		elseif(a.getSize() == 0){
			a.setActive(false);
			b.setActive(true);
		}
		else{

		}

		if()

}
	else{
		if(b,getSize() == 0 && !itemWasInserted){
			return;
		}
		elseif(b.getSize() == 0){
					b.setActive(false);
					a.setActive(true);
				}
		else{

		}

	}

}


for(int i =0 ; i < waitingtime.size() ; ++i)
{
	waitingtime[i+1] += waitingtime[i]
}

