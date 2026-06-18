/*
이 클래스는 단일 계정이 아니라, 생성된 모든 유저 계정 정보들을 관리하기 위한 클래스임.
따라서 여러 유저의 데이터를 조회하거나, 유저 목록을 수정하는 등의 함수는 이 클래스에 선언하되, 특정 유저의 데이터를 직접 수정하는 등의 함수는 이곳이 아닌 Account 클래스에서 구현해야 함.
*/
#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include "Account.h"
#include <list>
#include <string>

class AccountManager {
private:
	std::list<Account> account_list;
public:
	// 생성자
	AccountManager();

	// 계정 생성 관련 함수들
	void add_account_on_list();
	void remove_account_on_list(std::string user_id_for_delete);
	Account create_user_information();
	
	// 계정 조회 관련 함수들
	bool find_id_exists(std::string id_to_find);
	void show_existing_accounts();
};

#endif
