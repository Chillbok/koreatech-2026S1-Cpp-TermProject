#include "../include/Account.h"
#include <string>
#include <algorithm>
using std::string;

Account::Account() : id(""), password(""), points(0), total_purchase_amount(0) {}

Account::Account(string _id, string _password)
	: id(_id), password(_password), points(0), total_purchase_amount(0) {}

string Account::get_id() const { return id; }

bool Account::check_password_correct(string input) const {
	return input == this->password;
}

int Account::get_points() const { return points; }

int Account::get_total_purchase_amount() const { return total_purchase_amount; }

const std::vector<Cloth>& Account::get_purchase_history() const {
	return purchase_history;
}

void Account::set_points(int _points) { points = _points; }

void Account::set_total_purchase_amount(int _amount) { total_purchase_amount = _amount; }

void Account::add_points(int _points) { points += _points; }

void Account::add_purchase_amount(int _amount) { total_purchase_amount += _amount; }

void Account::add_cloth(const Cloth& cloth) {
	purchase_history.push_back(cloth);
}

bool Account::remove_cloth(const std::string& serial) {
	auto it = std::find_if(purchase_history.begin(), purchase_history.end(),
		[&serial](const Cloth& c) { return c.get_serial() == serial; });

	if (it == purchase_history.end()) {
		return false;
	}

	purchase_history.erase(it);
	return true;
}