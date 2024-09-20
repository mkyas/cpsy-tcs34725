
#include <iostream>
#include "TCS34725.hpp"

int main()
{
	float r, g, b;
	TCS34725 sensor;

	sensor.set_integration_time(2.4 * 8);
	sensor.set_gain(TCS34725::GAIN_1X);
	sensor.get_rgb(r, g, b);
	std::cout << r << " " << g << " " << b << " " << std::endl;
	return 0;
}
