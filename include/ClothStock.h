#ifndef CLOTH_STOCK_H
#define CLOTH_STOCK_H

#include <string>

struct ClothStock {
	std::string name;
	std::string color;
	std::string category;
	int price;
};

std::string generate_random_hash();

#endif
