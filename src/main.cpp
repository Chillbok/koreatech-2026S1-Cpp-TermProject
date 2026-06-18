/*
여기에는 컴파일 후 사용자의 모든 행동을 관리할 main 함수만 두도록 한다.
*/
#include <iostream>
using std::cout;
using std::endl;

#include "../include/ConsoleUtil.h"
#include "../include/Account.h"

int main() {
	ConsoleUtil::Opening();
	Account a;
	a.set_user_information();
	Account b("junho2", "password");
	return 0;
}