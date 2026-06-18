/*
여기에는 컴파일 후 사용자의 모든 행동을 관리할 main 함수만 두도록 한다.
*/
#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/Account.h"

// 작동하는지 확인하기 위한 임시 함수. 삭제 예정.
void show(Account& user_account) {
	cout << "유저의 아이디: " << user_account.get_id() << endl;
	cout << "유저의 비밀번호: " << user_account.get_password() << endl;
}

int main() {
	ConsoleUtil::Opening();
	Account a;
	a.set_user_information();
	Account b("junho2", "password");
	
	cout << endl;
	cout << ConsoleUtil::get_divider() << endl;
	cout << "a 객체의 사용자 정보" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	show(a);

	cout << endl;
	cout << ConsoleUtil::get_divider() << endl;
	cout << "b 객체의 사용자 정보" << endl;
	cout << ConsoleUtil::get_divider() << endl;
	show(b);
	return 0;
}