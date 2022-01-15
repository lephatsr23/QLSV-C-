#include "MyIO.h"
using namespace  std;

MyIO::MyIO() {

}

MyIO::~MyIO() {

}

void MyIO::writeToFile(string fileName, wstring data[], int size) {
	wofstream wof;
	wof.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wstring fileNameUTF = MyUnicode::StringToWString(fileName);
	wof.open(fileNameUTF);
	for (int i = 0; i < size; i++) {
		wof << data[i] << L"\n";
	}
	wof.close();
}
void MyIO::writeToCSVFile(string fileName, wstring data[], int size) {
	// Write file in UTF-8  
	std::wofstream wof;
	wof.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	wstring fileNameUTF = MyUnicode::StringToWString(fileName);
	wof.open(fileNameUTF);
	wstring temp;
	wstring line;
	for (int i = 0; i < size; i++) {
		//line = L"";
		temp = data[i];
		if (temp != L"") {
			wof << temp << L"\n";
		}
	}
	wof.close();
}

vector<wstring> MyIO::loadConfig(string fileName) {
	std::ifstream f(fileName);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(f.rdbuf());
	std::wistream wf(&conv);
	wchar_t BOM = 0xFEFF;
	unicode str[0x1000];
	unicode u;
	vector<wstring> result;
	wf.get(u);
	while (!wf.eof()) {
		wf.getline(str, 1000);
		result.push_back(str);
	}
	return result;
}
vector<wstring> MyIO::readDataFromFile(string fileName) {
	std::ifstream f(fileName);
	std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(f.rdbuf());
	std::wistream wf(&conv);
	wchar_t BOM = 0xFEFF;
	unicode str[0x1000];
	unicode u;
	vector<wstring> result;
	wf.get(u);
	while (!wf.eof()) {
		wf.getline(str, 1000);
		result.push_back(str);
	}
	return result;
}