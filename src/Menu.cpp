#include "../include/Menu.h"
#include "../include/ConsoleUtil.h"
#include <iostream>
using std::cout;
using std::endl;

void Menu::Opening() {
	using namespace ConsoleUtil;
	cout << get_divider() << endl;
	cout << "작성자: 이준호" << endl;
	cout << "학번: 2024100372" << endl;
	cout << get_divider() << endl;
	press_enter();
	clear_screen();
}
