#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class myStudent {
private:
	vector<wstring> _Data;
	int _CurrentColumn = 0;
public:
	myStudent();
	~myStudent();
	myStudent(vector<wstring> data);

	void resetCurrentColumn() { _CurrentColumn = 0; }
	wstring getNextColumnData();

	static int HeaderCount;
	static vector<wstring> Header;
	static vector<int> HeaderWidth;
	static vector<string> HeaderAlign;
	static vector<string> StudentTypes;

};