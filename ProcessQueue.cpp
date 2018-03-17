
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include "process.cpp"

class ProcessQueue{

private:
bool isActive;
std::deque<Process> p;

public:

ProcessQueue(bool isActive){
	this->isActive = isActive;
}

void add(Process newProcess){
	p.push_back(newProcess);
}

Process getTop() {
	return p.front();
}

void removeTop(){
	if (getLength() > 0) {
	p.pop_front();
	}
	else{
		std::cout << "Tried to remove an element when the length was empty";
	}
}

void sort(){
	std::sort(p.begin(), p.end(), sortingFunction);
}

bool sortingFunction(Process a, Process b) { return a.getPriority() < b.getPriority(); };

int getLength(){
	return p.size();
}

deque<Process> getProcessList(){
	return p;
}

bool getIsActive() {
	return isActive;
}

void setIsActive(bool value) {
	this->isActive = value;
}

};
