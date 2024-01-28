#pragma once

#include <Arduino.h>

enum class BLEPosDataType : uint8_t
{
	Goods = 0,
	Amount = 1,
	Sum = 2,
	Paid = 3
};