#include "neopixel.h"

bool NeoPixel::Set(const uint16_t led_id, const uint32_t color, const uint8_t brightness)
{
	if (led_id >= _led_number)
	{
		return false;
	}

	_neopixel.setPixelColor(led_id, color);
	_neopixel.setBrightness(brightness);
	_neopixel.show();

	return true;
}

bool NeoPixel::Set(const uint16_t led_id_begin, const uint16_t led_id_end, const uint32_t color, const uint8_t brightness)
{
	for (uint16_t i = led_id_begin; i < led_id_end; i++)
	{
		const bool result = Set(i, color, brightness);
		if (!result)
		{
			return false;
		}
	}

	return true;
}

bool NeoPixel::SetAll(const uint32_t color, const uint8_t brightness)
{
	return Set(0, _led_number - 1, color, brightness);
}

bool NeoPixel::Unset(const uint16_t led_id)
{
	return Set(led_id, unset_color, unset_brightness);
}

bool NeoPixel::Unset(const uint16_t led_id_begin, const uint16_t led_id_end)
{
	for (uint16_t i = led_id_begin; i < led_id_end; i++)
	{
		const bool result = Unset(i);
		if (!result)
		{
			return false;
		}
	}

	return true;
}

bool NeoPixel::UnsetAll()
{
	return Unset(0, _led_number - 1);
}