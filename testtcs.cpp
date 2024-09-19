
#include <iostream>
#include "TCS34725.hpp"

int main()
{
	TCS34725 sensor;
	std::array<std::uint16_t, 4> result{};
	sensor.get_raw(result);
	for (auto v : result) {
		std::cout << v << " ";
	}
	std::cout << std::endl;
	return 0;
}
