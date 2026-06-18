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
	cout << "서버 생성" << endl;
	Server main_server;
	
	cout << "계정 3개 생성" << endl;
	for (int i = 0; i < 3; ++i) main_server.get_account_manager().add_account_on_list();
	main_server.login();
	cout << "main 함수에 적음: 로그인 성공" << endl;
	
	cout << endl;
	cout << ConsoleUtil::get_divider() << endl;
	cout << "로그인한 계정 아이디: " << main_server.get_logged_in_account()->get_id() << endl;
	
	cout << "현재 계정 목록 보여줌" << endl;
	main_server.get_account_manager().show_existing_accounts();
	return 0;
}