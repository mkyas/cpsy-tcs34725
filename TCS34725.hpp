
#ifndef TCS34725_INCLUDED
#define TCS34725_INCLUDED

#include <cstdint>

#include <array>

class TCS34725
{
	static constexpr std::uint8_t ADDRESS = 0x29U;

	static constexpr std::uint8_t COMMAND_BIT = 0x80U;

	static constexpr std::uint8_t ENABLE      = 0x00U;
	static constexpr std::uint8_t ENABLE_PON  = 0x01U;
	static constexpr std::uint8_t ENABLE_AEN  = 0x02U;

	static constexpr std::uint8_t ATIME       = 0x01U;
	static constexpr std::uint8_t CONTROL     = 0x0FU;

	static constexpr std::uint8_t ID = 0x12U;

	static constexpr std::uint8_t CDATAL = 0x14U; /**< Clear channel data low byte */
	static constexpr std::uint8_t CDATAH = 0x15U; /**< Clear channel data high byte */
	static constexpr std::uint8_t RDATAL = 0x16U; 
	static constexpr std::uint8_t RDATAH = 0x17U;
	static constexpr std::uint8_t GDATAL = 0x18U;
	static constexpr std::uint8_t GDATAH = 0x19U;
	static constexpr std::uint8_t BDATAL = 0x1AU;
	static constexpr std::uint8_t BDATAH = 0x1BU;

public:
        enum integration_time : std::uint8_t {
		INTEGRATION_TIME_2P4MS = 0xFFU,
		INTEGRATION_TIME_24MS  = 0xF6U,
		INTEGRATION_TIME_50MS  = 0xEBU,
		INTEGRATION_TIME_101MS = 0xD5U,
		INTEGRATION_TIME_154MS = 0xC0U,
		INTEGRATION_TIME_700MS = 0x00U,
	};

	enum gain_t : std::uint8_t {
		GAIN_1X  = 0x00U,
		GAIN_4X  = 0x01U,
		GAIN_16X = 0x02U,
		GAIN_60X = 0x03U,
	};

	enum wait_time_t : std::uint16_t {
		WAIT_TIME_2P4MS  = 0x0FFU,
		WAIT_TIME_204MS  = 0x0ABU,
		WAIT_TIME_614MS  = 0x000U,
		WAIT_TIME_29MS   = 0x1FFU,
		WAIT_TIME_2450MS = 0x1ABU,
		WAIT_TIME_7400MS = 0x100U,
	};

private:
	int smbus;
	std::uint8_t address;
	std::uint8_t integration_time;
	gain_t gain;

public:
	explicit TCS34725(int smbus = 1, std::uint8_t address = TCS34725::ADDRESS);
	TCS34725(const TCS34725&) = delete;
	~TCS34725();

	void enable(void);
	void disable(void);
	void set_integration_time(std::uint8_t);
	void set_gain(gain_t);
	void get_raw(std::array<std::uint16_t, 4>&);
	void get_rgb(float&, float&, float&);
};

#endif
