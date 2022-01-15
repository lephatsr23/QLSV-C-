#include "myStack.h"
#include "myStudent.h"
using namespace std;

myStack::myStack() {
	_AvailableIndex = 0;
	_myStack = new myStudent[MAX_SIZE];
}

myStack::~myStack() {
	delete[] _myStack;
}

void myStack::push(myStudent student) {

	if (isFull()) return;
	_myStack[_AvailableIndex] = student;
	_AvailableIndex++;
	_Size++;
}

myStudent myStack::pop() {
	_AvailableIndex--;
	_Size--;
	return _myStack[_AvailableIndex];
}

myStudent myStack::peek() {
	return _myStack[_AvailableIndex];
}
bool myStack::isEmpty() {
	return _AvailableIndex == 0;
}
bool myStack::isFull() {
	return _AvailableIndex >= MAX_SIZE;
}

myStudent myStack::getNextData() {
	return _myStack[_CurrentIndex++];
}