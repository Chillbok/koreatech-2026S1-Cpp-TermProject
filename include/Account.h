/*
이 파일에는 사용자의 입출력을 담당하는 함수들을 저장한다.
*/
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
	std::string id;
	std::string password;
public:
	// 생성자
	Account();
	Account(std::string _id, std::string _password);
	
	// getter 함수
	std::string get_id();

	// 비밀번호 확인 함수
	bool check_password_correct(std::string input);
};

#endif
