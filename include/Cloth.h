#ifndef CLOTH_H
#define CLOTH_H

#include <string>

class Cloth {
private:
	std::string name;
	std::string color;
	std::string category;
	int price;
	int paid_price;
	int points_used;
	std::string serial;
public:
	Cloth();
	Cloth(std::string _name, std::string _color, std::string _category, int _price);

	std::string get_name() const;
	std::string get_color() const;
	std::string get_category() const;
	int get_price() const;
	int get_paid_price() const;
	int get_points_used() const;
	std::string get_serial() const;

	void set_name(std::string _name);
	void set_color(std::string _color);
	void set_category(std::string _category);
	void set_price(int _price);
	void set_paid_price(int _paid_price);
	void set_points_used(int _points_used);
	void set_serial(std::string _serial);
};

#endif
