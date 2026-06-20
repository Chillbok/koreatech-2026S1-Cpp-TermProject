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
	Menu::Opening();
	Server main_server = Menu::setup_server();
	
	Menu::ask_login(main_server);
	Menu::ask_logout(main_server);
	
	cout << "현재 계정 목록 보여줌" << endl;
	main_server.get_account_manager().show_existing_accounts();
	return 0;
}