#include "stdafx.h"
#include <deque>
#include <algorithm>
#include <iterator>
#include "process.cpp"

using namespace std;

class ProcessQueue {

private:
	bool isActive;
	

public:
	std::deque<Process*> p;
	ProcessQueue(bool isActive) {
		this->isActive = isActive;
	}

	void add(Process* newProcess) {
		p.push_back(newProcess);
	}

	Process* getTop() {
		return p.front();
	}

	void removeTop() {
		p.pop_front();
	}

	int getLength() {
		return p.size();
	}

	bool getIsActive() {
		return isActive;
	}

	void setIsActive(bool value) {
		this->isActive = value;
	}

	void incrTimesRun() {
		p.front()->incrTimesRun();
	}

	void setTimesRun(int timesRun) {
		p.front()->setTimesRun(timesRun);
	}

};
