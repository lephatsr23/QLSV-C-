#include "myStudent.h"
#include <iostream>

using namespace std;

myStudent::myStudent() {

}
myStudent::~myStudent() {

}

myStudent::myStudent(vector<wstring> data){
	_Data = data;
}

wstring myStudent::getNextColumnData() {
	/*if (_Data.empty()) return;*/
	return _Data[_CurrentColumn++];
}

int myStudent::HeaderCount = 9;
vector<wstring> myStudent::Header = { L"STT", L"Lớp", L"SBD", L"Tên", L"Chữ lót", L"Họ", L"Tuổi", L"Giới tính", L"Địa chỉ"};
vector<int> myStudent::HeaderWidth = { 5 ,10 , 10, 15, 15, 15, 12, 13, 0 };
vector<string> myStudent::HeaderAlign = { "center", "center", "center", "left", "left", "right", "center", "center", "left" };
vector<string> myStudent::StudentTypes = { "number", "string", "string", "string", "string", "string", "number", "string", "string" };
