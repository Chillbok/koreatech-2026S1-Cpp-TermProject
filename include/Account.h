#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Cloth.h"

class Account {
private:
	std::string id;
	std::string password;
	int points;
	int total_purchase_amount;
	int used_points;
	std::vector<Cloth> purchase_history;
public:
	Account();
	Account(std::string _id, std::string _password);

	std::string get_id() const;
	bool check_password_correct(std::string input) const;

	int get_points() const;
	int get_total_purchase_amount() const;
	const std::vector<Cloth>& get_purchase_history() const;
	int get_used_points() const;

	void set_points(int _points);
	void set_total_purchase_amount(int _amount);
	void add_points(int _points);
	void add_purchase_amount(int _amount);
	void subtract_purchase_amount(int _amount);
	void use_points(int pts);
	void restore_points(int pts);
	void recalculate_points();

	void add_cloth(const Cloth& cloth);
	bool remove_cloth(const std::string& serial);
};

#endif
