#pragma once

#include <Arduino.h>
#include <M5Stack.h>

class Power
{
public:
    static const uint8_t GetBatteryLevel()
    {
        return M5.Power.getBatteryLevel();
    }
};