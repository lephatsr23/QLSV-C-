#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h> 
#include "myStudent.h"
#include "myStack.h"
#include "MyUnicode.h"
#include "color.h"
#include "MyIO.h"

using namespace std;

#include"MyWindows.h"
using unicode = typename wchar_t; 

class MyCore
{
private:
	MyWindows _MyWindows;
	myStack _MyStudents;

public:
	
	MyCore(const unicode* title, int backgroundColor = 0, int foregroundColor = 7);
	~MyCore();
	void intro();
	void run() {
		listStudent();
	};
	void listStudent();
	void addStudent();
	void alert(wstring title [], int size, int closeTime = 3);
	void updateStudent();
	void printBottomCommands();
	void ByeBye();

private:
	wstring printHeader();
	wstring getHeader();
	wstring printFooter(int row);
	wstring headerPadding();
	wstring dataPadding();
	wstring printData(myStudent student, int row, int stt, boolean display =true);

	void saveData(string filename, boolean excel = false);
};

