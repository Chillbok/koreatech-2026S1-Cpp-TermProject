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
	
	// 함수
	void set_user_information();
	
	// getter 함수
	std::string get_id();
	std::string get_password();
};

#endif
