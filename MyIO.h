#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>
#include <vector>
#include <fstream> 
#include "MyUnicode.h" 

class MyIO
{
public:
	MyIO();
	~MyIO();

	static void writeToFile(string fileName, wstring data[], int size);
	static void writeToCSVFile(string fileName, wstring data[], int size);
	static vector<wstring> readDataFromFile(string fileName);
	static vector<wstring> loadConfig(string fileName);
};
