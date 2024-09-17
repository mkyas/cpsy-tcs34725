
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <sys/ioctl.h>

#include <fcntl.h>
#include <unistd.h>

#include <ctime>
#include <cstring>
#include <algorithm>
#include <stdexcept>

#include <iostream>

#include "TCS34725.hpp"



TCS34725::TCS34725(int smbus, std::uint8_t address) : smbus(0), address(address)
{
	char name[20];
	snprintf(name, sizeof(name) - 1, "/dev/i2c-%d", smbus);
	this->smbus = open(name, O_RDWR);
	if (this->smbus < 0) {
		// Exceptions are usually avoided or forbidden in embedded code.
		// We like to avoid some ideoms from embedded programming
		// to realise the RAII principle.
		throw std::runtime_error("Device does not exist");
	}

	if (ioctl(this->smbus, I2C_SLAVE, address & 0x7f) < 0) {
		throw std::runtime_error("Address not found");
	}

	static const constexpr std::array<std::uint8_t, 4> ids{ 0x4DU, 0x44U, 0x10U, 0x12U };

	std::uint8_t id = i2c_smbus_read_byte_data(this->smbus, TCS34725::ID);
	if (auto it = std::find(ids.cbegin(), ids.cend(), id); it == ids.cend()) {
		std::cerr << "Got id " << int{id} << std::endl;
		throw std::runtime_error("TCS34725: Wrong ID");
	}
	this->set_integration_time(this->integration_time);
	this->set_gain(this->gain);
	this->enable();
}

TCS34725::~TCS34725()
{
	close(this->smbus);
}

void TCS34725::enable(void)
{
	static const constexpr struct timespec threems = {0, 3000};
	i2c_smbus_write_byte_data(this->smbus, TCS34725::ENABLE, TCS34725::ENABLE_PON);
	nanosleep(&threems, nullptr);
	i2c_smbus_write_byte_data(this->smbus, TCS34725::ENABLE, TCS34725::ENABLE_PON | TCS34725::ENABLE_AEN);
	// TODO delay for integration time
}

void TCS34725::disable(void)
{
}

void TCS34725::set_integration_time(std::uint8_t it)
{
	i2c_smbus_write_byte_data(this->smbus, TCS34725::COMMAND_BIT | TCS34725::ATIME, it);
	this->integration_time = it;
}

void TCS34725::set_gain(TCS34725::gain_t gain)
{
	i2c_smbus_write_byte_data(this->smbus, TCS34725::COMMAND_BIT | TCS34725::CONTROL, gain);
	this->gain = gain;
}


void TCS34725::get_raw(std::array<std::uint16_t, 4> &result)
{
	result[3] = i2c_smbus_read_word_data(this->smbus, TCS34725::COMMAND_BIT | TCS34725::CDATAL);
	result[0] = i2c_smbus_read_word_data(this->smbus, TCS34725::COMMAND_BIT | TCS34725::RDATAL);
	result[1] = i2c_smbus_read_word_data(this->smbus, TCS34725::COMMAND_BIT | TCS34725::GDATAL);
	result[2] = i2c_smbus_read_word_data(this->smbus, TCS34725::COMMAND_BIT | TCS34725::BDATAL);

	// TODO: Add a delay for the integration time.

}

void TCS34725::get_rgb(float& r, float& g, float& b)
{

}
