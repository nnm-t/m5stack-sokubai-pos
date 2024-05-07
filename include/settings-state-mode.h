#pragma once

#include <Arduino.h>
#include <M5Stack.h>

enum class SettingsStateMode : uint8_t
{
    Time = 0,
    Brightness = 1
};