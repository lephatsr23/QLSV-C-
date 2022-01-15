#include "MyUnicode.h"
#include <iostream> 

wstring MyUnicode::ReadString() {
	unicode buffer[MAX_LENGTH];
	size_t numRead = 0;
	_cgetws_s(buffer, &numRead);
	return buffer;
}
void MyUnicode::ReadString(unicode* var) {
	unicode buffer[MAX_LENGTH];
	size_t numRead = 0;
	_cgetws_s(buffer, &numRead);
	for (size_t i = 0; i <= numRead; i++) {
		var[i] = buffer[i];
	}
}
void MyUnicode::ReadString(const unicode* subject, unicode* var) {
	WriteString(subject);
	ReadString(var);
}
void MyUnicode::ReadString(const char* subject, unicode* var) {
	WriteString(subject);
	ReadString(var);
}

int MyUnicode::ReadInt() {
	int so;
	scanf_s("%d", &so);
	getchar();
	return so;
}

void MyUnicode::WriteString(const unicode* string) {
	_cputws(string);
}
void MyUnicode::WriteString(const char* string) {
	cout << string;
}

int MyUnicode::Size(const unicode* string) {
	return wcslen(string);
}
int MyUnicode::Size(const char* string) {
	for (int i = 0; i < MAX_LENGTH; i++) {
		if (string[i] == EOL) {
			return i;
		}
	}
	return 0;
}

void MyUnicode::AppendString(unicode* left_string, const unicode* right_string) {
	int left_size = Size(left_string);
	int right_size = Size(right_string);
	int rigth_index = 0;
	for (int i = left_size; i < left_size + right_size; i++) {
		left_string[i] = right_string[rigth_index++];
	}
	left_string[left_size + right_size] = EOL;
}
void MyUnicode::AppendString(unicode* left_string, const char* right_string) {
	int left_size = Size(left_string);
	int right_size = Size(right_string);
	int rigth_index = 0;
	for (int i = left_size; i < left_size + right_size; i++) {
		left_string[i] = right_string[rigth_index++];
	}
	left_string[left_size + right_size] = EOL;
}

void MyUnicode::StringToUnicode(const char* string, unicode* var) {
	int string_size = Size(string);
	int i = 0;
	for (i = 0; i < string_size; i++) {
		var[i] = string[i];
	}
	var[i] = EOL;
}

wstring MyUnicode::StringToWString(const string& s) {
	wstring temp(s.length(), L' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp;
}