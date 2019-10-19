#pragma once

#include <Arduino.h>
#include <M5Stack.h>

class Power
{
public:
    static String GetBatteryLevel()
    {
        return String(M5.Power.getBatteryLevel());
    }
};