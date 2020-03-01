#pragma once

#include <Arduino.h>
#include <M5Stack.h>

enum class SettingsStateDateTime : uint8_t
{
    Year100 = 1,
    Year10 = 2,
    Year1 = 3,
    Month = 4,
    Day = 5,
    Hour = 6,
    Minute = 7
};