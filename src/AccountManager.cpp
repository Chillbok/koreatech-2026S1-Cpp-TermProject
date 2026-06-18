#include "../include/AccountManager.h"
#include <string>
using std::string;

AccountManager::AccountManager() : account_list() {}

void AccountManager::add_account_on_list() {
	account_list.emplace_back();
	// 아이디 생성 후 이미 존재하는 아이디인지 점검하는 과정은 여기에 구현하는 게 맞지 않을까?
	// 그럼 생성을 여기에서 관리하는 게 맞다고 본다. 매개변수를 제공해야 하는 Account 생성자를 사용해서 수정하고 말이다.
	account_list.back().set_user_information();
}

void AccountManager::remove_account_on_list(string user_id_for_delete) {
}
