#include "MyConfig.h"
#include "myStudent.h"
#include "common.h"
#include "MyIO.h"
#include "MyStack.h"
#include <vector>
MyConfig::MyConfig() {
}

MyConfig::~MyConfig() {
}

bool MyConfig::loadConfig() {
	vector<wstring> config = MyIO::loadConfig("config.txt");
	if (config.size() < 5) return false;

	int headerCount = 0;
	wstring temp = L"";
	myStudent::Header = {};
	wstring line = config[1] + L",";
	// "STT", "Lớp", "SBD", "Tên", "Chữ lót", "Họ", "Tuổi", "Giới tính", "Địa chỉ"
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			myStudent::Header.push_back(common::trim(temp));
			temp = L"";
			headerCount++;
		}
		else if (line[i] != L'\"') temp += line[i];
	}
	myStudent::HeaderCount = headerCount;

	headerCount = 0;
	temp = L"";
	myStudent::HeaderWidth = {};
	line = config[2] + L",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			myStudent::HeaderWidth.push_back(stoi(temp));
			temp = L"";
			headerCount++;
		}
		else {
			temp += line[i];
		}
	}
	if (myStudent::HeaderCount != headerCount) return false;

	headerCount = 0;
	temp = L"";
	myStudent::HeaderAlign = {};
	line = config[3] + L",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			string str(temp.begin(), temp.end());
			myStudent::HeaderAlign.push_back(common::trim(str));
			temp = L"";
			headerCount++;
		}
		else if (line[i] != L'\"') temp += line[i];
	}
	if (myStudent::HeaderCount != headerCount) return false;

	headerCount = 0;
	temp = L"";
	myStudent::StudentTypes = {};
	line = config[4] + L",";
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == L',') {
			string str(temp.begin(), temp.end());
			myStudent::StudentTypes.push_back(common::trim(str));
			temp = L"";
			headerCount++;
		}
		else if (line[i] != L'\"') temp += line[i];
	}
	if (myStudent::HeaderCount != headerCount) return false;

	return true;
}

void MyConfig::loadData(myStack& students) {
	vector<wstring> data = MyIO::readDataFromFile("hocsinh.csv");

	for (int i = 1; i < data.size(); i++) {
		if (data[i] != L"") {
			vector<wstring> dataLine;
			wstring temp = L"";
			wstring line = data[i] + L",";
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == L',') {
					dataLine.push_back(temp);
					temp = L"";
				}
				else if (line[i] != L'\"') temp += line[i];
			}
			students.push(myStudent(dataLine));
		}
	}
}
