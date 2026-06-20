#include "../include/ClothStock.h"
#include <random>
#include <iomanip>
#include <sstream>

std::string generate_random_hash() {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<std::uint64_t> dis;

	std::uint64_t value = dis(gen);

	std::ostringstream oss;
	oss << std::hex << std::setw(16) << std::setfill('0') << value;
	return oss.str();
}
