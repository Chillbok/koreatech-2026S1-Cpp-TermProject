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

string Account::get_id() { return id; }

bool Account::check_password_correct(string input) {
	return input == this->password;
}