#include "../include/ConsoleUtil.h"

#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <cstdlib>
using std::system;

void ConsoleUtil::opening() {
	cout << "이준호의 쇼핑몰" << endl;
}

void ConsoleUtil::clear_screen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

string ConsoleUtil::get_divider() {
	return "===================================";
}