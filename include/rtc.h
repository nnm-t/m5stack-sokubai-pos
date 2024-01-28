#pragma once

#include <Arduino.h>

#include "rtc-pcf8523.h"

class RTC
{
    RTC_PCF8523 _rtc;

public:
    RTC() : _rtc(RTC_PCF8523())
    {

    }

    void Begin();

    bool IsInitialized();

    DateTime GetNow();

    void Adjust(const DateTime& date_time);
};