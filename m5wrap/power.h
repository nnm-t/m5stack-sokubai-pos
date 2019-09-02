#pragma once

#include <Arduino.h>
#include <M5Stack.h>

namespace SokubaiPos
{
    class Power
    {
    public:
        static int8_t GetBatteryLevel()
        {
            return M5.Power.getBatteryLevel();
        }
    };
}