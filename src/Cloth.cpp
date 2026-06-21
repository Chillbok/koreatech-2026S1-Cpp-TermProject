#include "../include/Cloth.h"
#include "../include/ClothStock.h"
#include <string>
using std::string;

Cloth::Cloth() : name(""), color(""), category(""), price(0), paid_price(0), points_used(0), serial(generate_random_hash()) {}

Cloth::Cloth(string _name, string _color, string _category, int _price)
	: name(_name), color(_color), category(_category), price(_price), paid_price(_price), points_used(0), serial(generate_random_hash()) {}

string Cloth::get_name() const { return name; }
string Cloth::get_color() const { return color; }
string Cloth::get_category() const { return category; }
int Cloth::get_price() const { return price; }
int Cloth::get_paid_price() const { return paid_price; }
int Cloth::get_points_used() const { return points_used; }
string Cloth::get_serial() const { return serial; }

void Cloth::set_name(string _name) { name = _name; }
void Cloth::set_color(string _color) { color = _color; }
void Cloth::set_category(string _category) { category = _category; }
void Cloth::set_price(int _price) { price = _price; }
void Cloth::set_paid_price(int _paid_price) { paid_price = _paid_price; }
void Cloth::set_points_used(int _points_used) { points_used = _points_used; }
void Cloth::set_serial(string _serial) { serial = _serial; }
