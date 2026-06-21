#include "../include/ConsoleUtil.h"

#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
#include <cstdlib>
using std::system;

void ConsoleUtil::clear_screen() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

bool ConsoleUtil::get_player_confirm(string question_message) {
	while(true) {
		cout << question_message << "(y/n): ";
		string input;
		cin >> input;

		if (input == "y" || input == "Y") return true;
		else if (input == "n" || input == "N") return false;
		else {
			cerr << "[Error] 잘못된 글자를 작성하셨습니다. (y 또는 n)만 눌러주세요." << endl;
			continue;
		}
	}
}

void ConsoleUtil::press_enter() {
	cout << "[Enter]를 눌러 계속하기";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	string input;
	std::getline(std::cin, input);
}

string ConsoleUtil::get_divider() {
	return "===================================";
}