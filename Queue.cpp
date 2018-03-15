
#include <iostream>
#include <string>
#include <vector>
#include "process.cpp"

class Queue{

private:
int length;
bool isActive;
vector<Process> processList;

void swap(int index1, int index2){
Process temp = processList[index1];
processList[index1] = processList[index2];
processList[index2] = temp;
}

public:

Queue(bool isActive){
	this->length = 0;
	this->processList = [];
}

void add(){



}

Process remove(){
if(length == 0){
	return [];
}
}

void sort(){

	for(int i = 0; i < this->getLength() - 1; i++){
		for(int j = 0; j < this->getLength()-1-i; j++){
			if(processList[j].priority > proce)
		}
	}

}

int getLength(){
return length;
}

Process[] getProcessList(){
	return processList;
}

};
