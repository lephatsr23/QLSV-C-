#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include <windows.h> 
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "myStudent.h"
#include "MyWindows.h"
#include "MyStack.h"
#include "MyCore.h"
#include "color.h"


#define title L"Chương trình quản lý học sinh đơn giản "

int main() {
	MyCore MyPrograme(title, MyColors::BLUE, MyColors::WHITE);
	MyPrograme.intro();
	MyPrograme.run();
	char c = _getch();
	return 0;
}