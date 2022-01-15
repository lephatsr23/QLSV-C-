#pragma once
#include "myStudent.h"
using namespace std;


class myStack {
private:
	const int MAX_SIZE = 1000;
	int _AvailableIndex = 0;
	int _CurrentIndex = 0;
	int _Size = 0;
	myStudent* _myStack;
public:
	myStack();
	~myStack();
	void push(myStudent student);
	myStudent pop();
	myStudent peek();
	bool isEmpty();
	bool isFull();
	int size() {
		return  _Size;
	}
	void resetCurrentIndex() {
		_CurrentIndex = 0;
	}
	myStudent getNextData();
};