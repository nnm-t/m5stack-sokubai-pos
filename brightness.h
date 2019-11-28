#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "lcd.h"

class Brightness
{
    uint8_t _value;

    const uint8_t _step;

public:
    Brightness(const uint8_t initial, const uint8_t step) : _value(initial), _step(step)
    {

    }

    void Begin();

    void Up();

    void Down();
};