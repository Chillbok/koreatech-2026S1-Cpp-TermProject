#include "../include/Menu.h"
#include "../include/ConsoleUtil.h"
#include <iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
#include <string>
using std::string;

void Menu::opening() {
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

void Menu::start_menu(Server& s) {
	using namespace ConsoleUtil;
	while (true) {
		clear_screen();
		cout << "해당하는 번호를 눌러 행동을 선택하세요." << endl;
		cout << "\t1. 로그인" << endl;
		cout << "\t2. 계정 생성" << endl;
		cout << "\t3. 로그아웃" << endl;
		cout << "\t4. 계정 목록 조회" << endl;
		cout << "\t5. 옷 검색" << endl;
		cout << "\t0. 종료" << endl;

		int action_number;
		cin >> action_number;

		switch (action_number) {
			case 1:
				ask_login(s);
				break;
			case 2:
				s.signup();
				break;
			case 3:
				ask_logout(s);
				break;
			case 4:
				s.get_account_manager().show_existing_accounts();
				press_enter();
				break;
			case 5:
				break;
			case 0:
				return;
			default:
				cerr << "[Error] 잘못된 입력입니다." << endl;
				press_enter();
				break;
		}
	}
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

	press_enter();
	clear_screen();

	// 계정이 있다면
	bool no_account_ask_player = get_player_confirm("로그인하시겠습니까?");
	if (no_account_ask_player == true) {
		cout << "로그인을 시작합니다." << endl;
		s.login();
	}
	else {
		cout << "취소를 선택하셨습니다. 비회원 상태를 유지합니다. 비회원의 구매는 저장되지 않습니다." << endl;
	}
	press_enter();
	clear_screen();
}

void Menu::ask_logout(Server& s) {
	Account* current_account = s.get_logged_in_account();
	if(current_account == nullptr) {
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