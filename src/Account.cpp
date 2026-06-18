#include "../include/Account.h"
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;

Account::Account() : id(""), password("") {}

Account::Account(string _id, string _password) : id(_id), password(_password) {}

void Account::set_user_information() {
	string input;
	cout << "아이디 입력: ";
	cin >> input;
	// 여기에 중복되는 아이디가 있는지 점검하는 과정이 필요할듯
	
	id = input;
	while(true) {
		input.clear();
		string temp_password;
		cout << "비밀번호 입력: ";
		cin >> input;
		temp_password = input;
		input.clear();
		cout << "비밀번호 다시 입력: ";
		cin >> input;
		
		if (temp_password == input) {
			cout << "비밀번호 일치함." << endl;
			this->password = temp_password;
			break;
		}
		
		cerr << "[Error] 비밀번호 불일치함. 다시 입력하세요." << endl;
		cout << endl;
	}
}

string Account::get_id() { return id; }
string Account::get_password() { return password; }