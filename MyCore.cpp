#include "MyCore.h"
#include "MyConfig.h"
#include "common.h"
#include <locale>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <conio.h>
#include <windows.h> 
#include <iostream>

MyCore::MyCore(const unicode* title, int backgroundColor , int foregroundColor) {
	int width = 150;
	int height = 30;
	// khoi tao 1 cai windows
	_MyWindows = MyWindows(0, 0, width, height, 1, backgroundColor, foregroundColor);
	// tat con tro nhap nhay
	_MyWindows.showConsoleCursor(false);
	// clear console
	_MyWindows.clearConsole();
	// ve khung
	_MyWindows.drawFrame();
	// viet gi do
	_MyWindows.write(title, (width - MyUnicode::Size(title)) / 2, 0, MyColors::RED, MyColors::WHITE);
	// load data
	MyConfig::loadData(_MyStudents);
	int a = 0;
}

MyCore::~MyCore() {

}
void MyCore::intro(){
	// lay dai, cao, rong, toa do x y: rong width - 20 cao 80 h = 17, x = (width - w) / 2, y = (height - h) / 2
	int w = _MyWindows.getWidth() - 20;
	int h = 17;
	int x = (_MyWindows.getWidth() - w) / 2;
	int y = (_MyWindows.getHeight() - h) / 2;

	// save cai screen
	_MyWindows.saveScreenRect(x,y,w,h);
	// title loi gioi thieu
	unicode title[] = L"Chương trình quản lý sinh viên";
	// chon mau cho nen va chu
	int background = MyColors::LIGHTBLUE;
	int foreground = MyColors::WHITE;
	// tao chuyen dong
	// tao windows intro nho
	MyWindows introWin(x, y, w, h, 0, background, foreground);
	// clearconsole trong windows
	introWin.clearConsole();
	// ve khung 
	introWin.drawFrame();
	// viet tieu de
	introWin.write(title, (w - MyUnicode::Size(title)) / 2, 0, MyColors::BROWN, foreground);
	// bat dau tu dong 2 va cot 2
	int row = 2;
	int col = 2; 
	introWin.write(L"Đây là chương trình quản lý sinh viên có giao điện", col, row++, background, foreground);
	// ghi noi dung " day la chuong trinh quan ly hoc sinh don gian" tang row hang len
	introWin.write(L"Học tư duy lập trình C++", col, row++, background, foreground);
	introWin.write(L"Dựa trên HuyQLSV", col, row++, background, foreground);
	introWin.write(L"viêt theo psudocode", col, row++, background, foreground);
	introWin.write(L"Người làm TLHPHAT", col, row++, background, foreground);
	introWin.write(L"Năm: 2022", col, row++, background, foreground);
	introWin.write(L"nhấn phím bất kì để đóng", col, row++, background, foreground);
	// ghi noi dung " nhấn phím bất kì để đóng" tang row hang len 
	int c = _getch() -48;
	_MyWindows.restoreScreenRect();
}
void MyCore::listStudent(){
	// call function updateStudentList();
 	updateStudent();
	// call printBottomCommands();
	printBottomCommands();
	// khoi tao x cho bang phim
	unsigned int x = _getch();
	int countDown = 5;
	wstring messages[10];
	// khoi tao countDown = 2
	// khoi tao messages[10];
	while (x != 24) { // x = 24 Thoat ctrl + x 
		if (x == 19) { // x = 19 Luu danh vao van ban file txt ctrl + s
			saveData("hocsinh", false);
			messages[0] = L"Danh sách đã lưu dưới dạng văn bản !";
			alert(messages, 1, countDown);
			// goi ham savedata vao file txt
		}
		else if (x == 3) { // x = 3 Luu danh sach vao excel // ctrl +c 
			// goi ham savedata vao file excel
			saveData("hocsinh", true);
			messages[0] = L"Danh sách đã lưu dưới dạng Excel !";
			alert(messages, 1, countDown);
		}
		else if(x == 1) { // x = 1 Da them 1 hoc sinh // ctrl + a
			// goi ham add sinh vien 
			addStudent();
			messages[0] = L"Đã thêm 1 học sinh!";
			messages[1] = L"Danh sách đang có :" + to_wstring(_MyStudents.size()) + L" học sinh !";
			alert(messages, 1, countDown);
			updateStudent();
		}
		else if (x == 5) { // x = 5 soan 1 hoc sinh // ctrl + e
			// goi ham  soan hoc sinh ( chỉnh sửa)
			messages[0] = L"Soạn 1 học sinh!";
			alert(messages, 1, countDown);
		}
		x = _getch();
	}
	ByeBye();
}
void MyCore::addStudent(){
	// thiet lap w 50 h headercount +3  x width -w / 2 y heigh -h /2
	int w = 50; 
	int h = myStudent::HeaderCount + 3;
	int x = ( _MyWindows.getWidth() - w) / 2;
	int y = ( _MyWindows.getHeight() - h) / 2;

	// save screen 
	_MyWindows.saveScreenRect(x,y,w,h);

	unicode title[] = L"thêm học sinh";
	int background = MyColors::LIGHTMAGENTA;
	int foreground  = MyColors::WHITE;
	_MyWindows.animateFrame(x, y, w, h, background, foreground);// toa chuyen dong 
	//khoi tao console
	MyWindows console(x, y, w, h, 0, background, foreground);
	console.clearConsole();// xoa console
	console.drawFrame();// ve khung
	console.write(title, (w - MyUnicode::Size(title)) / 2, 0, MyColors::BROWN, foreground);// viet tieu de
	int row = 2;// row 2 
	int col = 2;// col 2 
	wstring temp;// khoi tao temp : bien luu du dieu;
	vector<wstring> data;// khoi tao vector string data
	console.showConsoleCursor(true);// hien thi con tro tren console
	for (int i = 0; i < myStudent::HeaderCount; i++)
	{
		temp = myStudent::Header[i] + L" "; // lay tung du lieu tu mang head[i]
		console.write(temp, col, row, background, foreground);// viet len console
		console.gotoXY(temp.length() +2, row++);
		if (myStudent::StudentTypes[i] == "number") {
			data.push_back(to_wstring(MyUnicode::ReadInt()));
		}
		else {
			data.push_back(MyUnicode::ReadString());
		}
	}
	myStudent student(data);
	_MyStudents.push(student);	// _Student push(student)
	console.showConsoleCursor(false); 	// tat cursor (false);
	_MyWindows.restoreScreenRect(); 	// restoreScreenRect();

}
void MyCore::alert(wstring title[], int size, int closeTime){
	int w = 50; 
	int h = size + 4; 
	int x = (_MyWindows.getWidth() - w) / 2;
	int y = (_MyWindows.getHeight() - h) / 2;
	//khoi tao  w =50 h = size + 4 x = getwidth -w /2 y = getheight - h /2 
	_MyWindows.saveScreenRect(x, y, w, h);// sau screen chinh
	int background = MyColors::LIGHTMAGENTA;// background = lightmagenta
	int foreground = MyColors::WHITE;// foreground white 
	_MyWindows.animateFrame(x,y,w,h,background,foreground); // tao chuyen dong cham 
	MyWindows infor(x, y, w, h, 0, background, foreground);  // tao bang thong bao
	infor.clearConsole(); // clear ban thong bao

	infor.drawFrame();// ve ban 
	// viet thong bao L=" thông báo" ở đầu bản chon màu nâu và foreground 
	wstring temp = L" Thông báo ";
	infor.write(temp, (w - temp.length()) / 2, 0, MyColors::BROWN, foreground);
	for (int i = 0; i < size; i++)
	{
		infor.write(title[i], (w - temp.length()) / 2 - 4 , 2 + i, MyColors::BROWN, foreground);
	}

	// viet tung thong bao vao theo size 
	temp = L" Đóng trong ";
	infor.write(temp, (w - temp.length()) / 2, h+4, MyColors::BROWN, foreground);
	for (int i = closeTime ; i > 0; i--)
	{
		temp = L" Đóng trong " + to_wstring(i) + L" giây";
		infor.write(temp, (w - temp.length()) / 2, h -1, MyColors::BROWN, foreground);
		Sleep(1000);
	}
	
	// chạy dếm ngược 1 giây 
	
	_MyWindows.restoreScreenRect();// goi lai windowns chính
}
void MyCore::updateStudent(){
	_MyWindows.write(L" Số học sinh " + to_wstring(_MyStudents.size()) + L" ", 1, 1, MyColors::GREEN, MyColors::WHITE);//viet vai windows "Số học sinh "
	_MyStudents.resetCurrentIndex();// reset index hoc sinh
	printHeader();// in header
	int row = 4;// in data hoc sinh 
	int stt = 1;// int print Footer(++row);
	for (int i = 0; i < _MyStudents.size(); i++) {
		row++;
		printData(_MyStudents.getNextData(), row, stt++, 1);
		if (row + 5 > _MyWindows.getHeight()) break;
	}// reset index hoc sinh
	printFooter(++row);
	_MyStudents.resetCurrentIndex();
}
void MyCore::printBottomCommands(){

	int col = 1;
	int row = _MyWindows.getHeight() - 1;
	wstring temp = L" Ctrl + s ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);
	col += temp.size();
	temp = L" lưu vô văn bản";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + c ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);
	col += temp.size();
	temp = L" Xuất ra excel ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + a ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);
	col += temp.size();
	temp = L" Thêm ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + e ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);
	col += temp.size();
	temp = L" Soạn ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);

	col += temp.size() + 3;
	temp = L" Ctrl + X ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);
	col += temp.size();
	temp = L" Thoát ";
	_MyWindows.write(temp, col, row, MyColors::BLUE, MyColors::WHITE);
}
void MyCore::ByeBye() {
	int row = ((_MyWindows.getHeight() - 8) / 2);
	_MyWindows.clearConsole();// clear console
	wstring byebye = L"";// tao chu byebye
	byebye = L"                                                         ";
	int col = (_MyWindows.getWidth() - byebye.size()) / 2;
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	byebye = L"██████╗ ██╗   ██╗███████╗      ██████╗ ██╗   ██╗███████╗ ";
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	byebye = L"██╔══██╗╚██╗ ██╔╝██╔════╝      ██╔══██╗╚██╗ ██╔╝██╔════╝ ";
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	byebye = L"██████╔╝ ╚████╔╝ ██████╗       ██████╔╝ ╚████╔╝ █████╗   ";
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	byebye = L"██╔══██╗  ╚██║   ██╔═══╝       ██╔══██╗  ╚██║   ██╔══╝   ";
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	byebye = L"██████╔╝   ██║   ███████╗      ██████╔╝   ██║   ███████╗ ";
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	byebye = L"╚═════╝    ╚═╝   ╚══════╝      ╚═════╝    ╚═╝   ╚══════╝ ";
	_MyWindows.write(byebye, col, row++, MyColors::BROWN, MyColors::DARKGRAY);
	// tu dong thoat trong 5 giay


}

void::MyCore::saveData(string filename, boolean excel) {
	wstring data[MAX_LENGTH]; // khoi tao data[maxlength]
	int size = 0;// khoi tao size =0
	_MyStudents.resetCurrentIndex(); // resetcurrentIndex trong student
	wstring line; // khoi tao line la wstring
	if (excel) { // kiem tra la excel khong? line = getHeader, line =prinheader();
		line = getHeader();
	}
	else {
		line = printHeader();
	}
	data[size++] = line; // data[0] = line;
	for (int i = 0; i < _MyStudents.size(); i++)
	{
		line = printData(_MyStudents.getNextData(), 0, size, !excel);
		data[size] = line;
		size++;
	}
	if (!excel) {
		line = printFooter(0);
		data[size++] = line;
	}
	_MyStudents.resetCurrentIndex();

	if (excel) {
		MyIO::writeToCSVFile(filename + ".csv", data, size);
	}
	else {
		MyIO::writeToFile(filename + ".txt", data, size);
	}

}

wstring MyCore::printHeader(){
	wstring top = L"┌";// khoi tao top = 'r'  line = L""; bottom = L"├"; 
	wstring line = L"";
	wstring bottom = L"├";
	int w = 0;// khoi tao w =0
	// kiem tra i toi cuoi mang headerWidth;
	// top    ┌---┬----┐  HuyCommon::headerPadding(HuyStudent::Header[i], HuyStudent::HeaderWidth[i], L" ");
	// line   | w |    |  
	// bottom ├---┼----┤   HuyCommon::headerPadding(L"", column.length(), L"─");
	for (int i = 0; i < myStudent::HeaderCount; i++)
	{
		line += L"│";
		w += myStudent::HeaderWidth[i] + 1;
		wstring column;
		if (myStudent::HeaderWidth[i] > 0) {
			column = common::headerPadding(myStudent::Header[i], myStudent::HeaderWidth[i], L" ");
		}
		else{
			column = common::headerPadding(myStudent::Header[i], _MyWindows.getWidth() - w - 3, L" ");
		}	
		top += common::headerPadding(L"", column.length(), L"-");
		if (i < myStudent::HeaderCount - 1) { top += L"┬"; }
		line += column;
		bottom += common::headerPadding(L"", column.length(), L"-");
		if (i < myStudent::HeaderCount - 1) { bottom += L"┼"; }
	}
	top += L"┐";
	line += L"│";
	bottom += L"┤";
	_MyWindows.write(top, 1, 2, MyColors::LIGHTMAGENTA, MyColors::WHITE);
	_MyWindows.write(line, 1, 3, MyColors::LIGHTMAGENTA, MyColors::WHITE);
	_MyWindows.write(bottom, 1, 4, MyColors::LIGHTMAGENTA, MyColors::WHITE);
	return top + L"\n" + line + L"\n" + bottom;
}
wstring MyCore::getHeader(){ // tra header
	wstring line; // khoi tao wstring line, w =0
	for (int i = 0; i < myStudent::HeaderCount; i++)
	{
		line += L"\"";
		line += common::trim(myStudent::Header[i]);
		line += L"\",";
	}
	
	return line.substr(0, line.size() - 1);
}
wstring MyCore::printFooter(int row){
	wstring line = L"L"; // khoi tao  line = L""; 
	int w = 0; // khoi tao w =0
	// kiem tra i toi cuoi mang headerWidth;
	//                 HuyCommon::headerPadding(L"", HuyStudent::HeaderWidth[i], L"─");
	// line └------┘   HuyCommon::headerPadding(L"", _HuyWindows.getWidth() - w - 3, L"─");
	for (int i = 0; i < myStudent::HeaderCount; i++)
	{
		wstring column;
		if (myStudent::HeaderWidth[i] > 0) {
			column = common::headerPadding(L"", myStudent::HeaderWidth[i], L"-");
		}
		else {
			column = common::headerPadding(L"", _MyWindows.getWidth(), L"-");
		}
		line += column;
		if (i < myStudent::HeaderCount - 1) line += L"┴";
	}
	line += L"┘";

	if( row > 0) _MyWindows.write( line, 1, row, MyColors::LIGHTBLUE, MyColors::WHITE);
	return line; // line;
}
wstring MyCore::headerPadding(){
	return 0;
}
wstring MyCore::dataPadding(){
	return 0;
}
wstring MyCore::printData(myStudent student, int row, int stt, boolean display){
	wstring line = L"";
	int w = 0;
	student.resetCurrentColumn();
	for (int i = 0; i < myStudent::HeaderCount; i++) {
		if (display) {
			line += L"│";
		}
		else
		{
			line += L"\"";
		}
		w += myStudent::HeaderWidth[i] + 1;
		wstring column;
		wstring data = student.getNextColumnData();
		if (i == 0) data = to_wstring(stt);
		if (display) {
			if (myStudent::HeaderWidth[i] > 0) {
				column = common::dataPadding(data, myStudent::HeaderWidth[i], myStudent::HeaderAlign[i], display);
			}
			else {
				column = common::dataPadding(data, _MyWindows.getWidth() - w - 3, myStudent::HeaderAlign[i], display);
			}
		}
		else {
			column = common::trim(data) + L"\",";
		}
		line += column;
	}
	if (display) {
		line += L"│";
	}
	else
	{
		line = line.substr(0, line.size() - 1);
	}
	if (display && row > 0) _MyWindows.write(line, 1, row, MyColors::LIGHTBLUE, MyColors::WHITE);
	return line;
}