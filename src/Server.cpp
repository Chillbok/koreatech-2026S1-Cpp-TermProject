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

Server::Server() : account_manager(), logged_in_account(nullptr) {
	
}

void Server::login() {
	// 계정 개수 확인하고, 계정이 없다면 생성하도록 유도하는 코드가 필요함.
	cout << endl;
	cout << "로그인" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	string input;
	
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
		break;
	}
}

void Server::logout() {
	cout << endl;
	cout << "# 로그아웃 절차 시작" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	logged_in_account = nullptr;
	cout << "로그아웃 되었습니다." << endl;
}

Account* Server::get_logged_in_account() { return logged_in_account; }
AccountManager& Server::get_account_manager() { return account_manager; }