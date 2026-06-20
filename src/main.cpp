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
	
	// 새로운 코드
	cout << endl;
	cout << "# 서버 생성 절차 시작" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	Server main_server;
	
	for (int i = 0; i < 2; ++i) {
		cout << i+1 << "번째 계정 생성" << endl;
		main_server.get_account_manager().add_account_on_list();
		ConsoleUtil::clear_screen();
	}
	
	bool start_login = ConsoleUtil::get_player_confirm("로그인할까요?");
	if (start_login == true) {
		main_server.login();
		ConsoleUtil::clear_screen();
	
		main_server.show_logged_in_id();
		bool logout = ConsoleUtil::get_player_confirm("로그아웃할까요?");
		if (logout == true) main_server.logout();
		else cout << "로그인 상태 유지됨" << endl;
		ConsoleUtil::clear_screen();
	}
	
	cout << "현재 계정 목록 보여줌" << endl;
	main_server.get_account_manager().show_existing_accounts();
	return 0;
}