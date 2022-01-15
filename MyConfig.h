#pragma once
using namespace std;
#include "common.h"
#include "myStack.h"

class MyConfig
{
public:
	MyConfig();
	~MyConfig();

	static bool loadConfig();
	static void loadData(myStack& students);
};


