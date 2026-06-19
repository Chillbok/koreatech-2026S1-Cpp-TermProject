/*
여기에는 컴파일 후 사용자의 모든 행동을 관리할 main 함수만 두도록 한다.
*/
#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/AccountManager.h"
#include "../include/Server.h"

int main() {
	ConsoleUtil::Opening();
	cout << ConsoleUtil::get_divider() << endl;
	
	// 새로운 코드
	cout << endl;
	cout << "# 서버 생성 절차 시작" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	Server main_server;
	
	/*
	for (int i = 0; i < 3; ++i) main_server.get_account_manager().add_account_on_list();
	*/
	main_server.login();
	
	main_server.show_logged_in_id();
	main_server.logout();
	
	cout << "현재 계정 목록 보여줌" << endl;
	main_server.get_account_manager().show_existing_accounts();
	return 0;
}