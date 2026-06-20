#include "../include/Menu.h"
#include "../include/ConsoleUtil.h"
#include <iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
#include <string>
using std::string;

void Menu::Opening() {
	using namespace ConsoleUtil;
	cout << get_divider() << endl;
	cout << "작성자: 이준호" << endl;
	cout << "학번: 2024100372" << endl;
	cout << get_divider() << endl;
	press_enter();
	clear_screen();
}

Server Menu::setup_server() {
	using namespace ConsoleUtil;
	cout << endl;
	cout << "서버 생성 절차 시작" << endl;
	press_enter();
	clear_screen();

	Server server;

	cout << "서버 생성 완료" << endl;
	press_enter();
	clear_screen();
	return server;
}

void Menu::ask_login(Server& s) {
	using namespace ConsoleUtil;
	string input;
	int account_list_size = s.get_account_manager().get_account_list_size();
	// 계정이 없다면
	if (account_list_size < 1) {
		bool no_account_ask_player = get_player_confirm("서버에 계정이 없습니다. 생성하시겠습니까?");
		if (no_account_ask_player == true) {
			cout << "계정 생성을 시작합니다." << endl;
			s.get_account_manager().add_account_on_list();
		}
		else cout << "취소를 선택하셨습니다. 비회원 상태를 유지합니다. 비회원의 구매는 저장되지 않습니다." << endl;
	}
	// 계정이 있다면
	else {
		bool no_account_ask_player = get_player_confirm("로그인하시겠습니까?");
		if (no_account_ask_player == true) {
			cout << "로그인을 시작합니다." << endl;
			s.login();
		}
		else {
			cout << "취소를 선택하셨습니다. 비회원 상태를 유지합니다. 비회원의 구매는 저장되지 않습니다." << endl;
		}
	}
	press_enter();
	clear_screen();
}

void Menu::ask_logout(Server& s) {
	if(s.get_logged_in_account() == nullptr) {
		cout << "로그아웃 할 필요가 없습니다." << endl;
	}
	else {
		bool user_confirm = ConsoleUtil::get_player_confirm("로그아웃 하시겠습니까?");
		if (user_confirm == true) s.logout();
		else cout << "로그아웃 완료." << endl;
	}
	ConsoleUtil::press_enter();
	ConsoleUtil::clear_screen();
}