#include "../include/AccountManager.h"
#include "../include/Account.h"
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;

AccountManager::AccountManager() : account_list() {}

void AccountManager::add_account_on_list() {
	account_list.push_back(create_user_information());
}

void AccountManager::remove_account_on_list(string user_id_for_delete) {
}

Account AccountManager::create_user_information() {
	string input, temp_id, temp_password;

	// 아이디 설정 단계
	while(true) {
		cout << "생성할 아이디 입력: ";
		cin >> input;

		// 유저 리스트에서 같은 아이디 발견
		if (find_id_exists(input) == true) {
			cerr << "[Error] 중복된 아이디입니다. 다른 아이디를 입력하세요." << endl;
			continue;
		}
		
		temp_id = input;
		cout << "아이디 설정 완료: " << temp_id << endl;
		break;
	}
	
	// 비밀번호 설정 단계
	while(true) {
		cout << "생성할 비밀번호 입력: ";
		cin >> temp_password;
		cout << "비밀번호 다시 입력: ";
		cin >> input;
		
		// 다시 입력한 비밀번호가 틀렸으면
		if (input != temp_password) {
			cerr << "[Error] 비밀번호가 일치하지 않습니다. 다시 입력하세요." << endl;
			continue;
		}
		cout << "비밀번호 설정 완료" << endl;
		break;
	}

	return Account(temp_id, temp_password);
}

bool AccountManager::find_id_exists(string id_to_find) {
	for (Account& existing_account : account_list) {
		if (id_to_find == existing_account.get_id()) return true;
	}
	return false;
}
