#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "lcd.h"

class Brightness
{
    uint8_t _value;

    const uint8_t _step;

public:
    static constexpr uint8_t max = 255;
    static constexpr uint8_t min = 0;

    Brightness(const uint8_t initial, const uint8_t step) : _value(initial), _step(step)
    {

    }

    void Begin();

    void Up();

    void Down();

    const uint8_t GetValue()
    {
        return _value;
    }
};