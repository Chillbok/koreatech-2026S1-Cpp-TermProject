/*
여기에는 컴파일 후 사용자의 모든 행동을 관리할 main 함수만 두도록 한다.
*/
#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/AccountManager.h"

int main() {
	ConsoleUtil::Opening();
	cout << ConsoleUtil::get_divider() << endl;
	
	AccountManager acc_manager;
	acc_manager.add_account_on_list();
	acc_manager.add_account_on_list();
	acc_manager.add_account_on_list();
	acc_manager.remove_account_on_list("junho");

	system("clear");
	cout << "저장된 계정 정보 출력" << endl;
	acc_manager.show_existing_accounts();
	return 0;
}