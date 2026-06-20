#ifndef CLOTH_H
#define CLOTH_H

#include <string>

class Cloth {
private:
	std::string name;
	std::string color;
	std::string category;
	int price;
	std::string serial;
public:
	Cloth();
	Cloth(std::string _name, std::string _color, std::string _category, int _price);

	std::string get_name() const;
	std::string get_color() const;
	std::string get_category() const;
	int get_price() const;
	std::string get_serial() const;

	void set_name(std::string _name);
	void set_color(std::string _color);
	void set_category(std::string _category);
	void set_price(int _price);
	void set_serial(std::string _serial);
};

#endif
