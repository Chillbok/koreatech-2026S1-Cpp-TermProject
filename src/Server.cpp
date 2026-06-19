#include "../include/Server.h"
#include "../include/Account.h"
#include "../include/ConsoleUtil.h"
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;

Server::Server() : account_manager(), logged_in_account(nullptr), logged_in(false) {
	cout << "서버 생성 및 변수 초기화 완료" << endl;
}

void Server::login() {
	cout << endl;
	cout << "로그인" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	string input;
	// 계정 개수 확인하고, 계정이 없다면 생성하도록 유도하는 코드가 필요함.
	if (account_manager.get_account_list_size() == 0) {
		cout << "계정 없음. 계정 생성 단계로 넘어갑니다." << endl;
		account_manager.add_account_on_list();
	}
	
	// 아이디 입력 단계
	while(true) {
		cout << "아이디(종료하려면 'q' 입력): ";
		cin >> input;

		if (input == "q") {
			cout << "로그인을 취소합니다." << endl;
			return;
		}

		if (account_manager.define_id_exists(input) == false) {
			cerr << "[Error] 아이디 없음. 다시 입력하세요." << endl;
			continue;
		}
		
		logged_in_account = account_manager.get_account_by_id(input);
		break;
	}
	
	while(true) {
		cout << "비밀번호(종료하려면 'q' 입력): ";
		cin >> input;

		if (input == "q") {
			cout << "로그인을 취소합니다." << endl;
			logged_in_account = nullptr;
			return;
		}
		
		if (logged_in_account->check_password_correct(input) == false) {
			cerr << "[Error] 비밀번호가 틀립니다. 다시 입력하세요." << endl;
			continue;
		}
		
		cout << "로그인 성공!" << endl;
		logged_in = true;
		break;
	}
}

void Server::logout() {
	cout << endl;
	
	if (logged_in == false) {
		cerr << "[Error] 로그인된 계정 없음. 로그아웃 불가능." << endl;
		return;
	}

	cout << "# 로그아웃 절차 시작" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	logged_in_account = nullptr;
	logged_in = false;
	cout << "로그아웃 되었습니다." << endl;
}

void Server::show_logged_in_id() {
	if (logged_in == false) {
		cerr << "[Error] 로그인된 계정 없음." << endl;
		return;
	}
	cout << "현재 로그인된 계정: " << logged_in_account->get_id() << endl;
}

Account* Server::get_logged_in_account() { 
	cout << endl;
	cout << "# 로그인된 계정 확인하기" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	if (logged_in == false) {
		cerr << "[Error] 로그인된 계정 없음." << endl;
		return nullptr;
	}
	return logged_in_account;
}
AccountManager& Server::get_account_manager() { return account_manager; }