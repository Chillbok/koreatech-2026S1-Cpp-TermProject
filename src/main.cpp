/*
여기에는 컴파일 후 사용자의 모든 행동을 관리할 main 함수만 두도록 한다.
*/
#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/Menu.h"
#include "../include/AccountManager.h"
#include "../include/Server.h"

int main() {
	Menu::opening();
	Server main_server = Menu::setup_server();
	Menu::start_menu(main_server);
	
	return 0;
}