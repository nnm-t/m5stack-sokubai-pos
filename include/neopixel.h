#pragma once

#include <M5Stack.h>
#include <Adafruit_NeoPixel.h>

class NeoPixel
{
	static constexpr const uint32_t unset_color = 0x000000;
	static constexpr const uint8_t unset_brightness = 0x00;

	Adafruit_NeoPixel _neopixel;
	const uint16_t _led_number;

public:
	NeoPixel(const uint16_t led_number = 10, const uint16_t gpio = 15) : _neopixel(Adafruit_NeoPixel(led_number, gpio)), _led_number(led_number)
	{

	}

	void Begin()
	{
		_neopixel.begin();
	}

	bool Set(const uint16_t led_id, const uint32_t color, const uint8_t brightness);

	bool Set(const uint16_t led_id_begin, const uint16_t led_id_end, const uint32_t color, const uint8_t brightness);

	bool SetAll(const uint32_t color, const uint8_t brightness);

	bool Unset(const uint16_t led_id);

	bool Unset(const uint16_t led_id_begin, const uint16_t led_id_end);

	bool UnsetAll();
};