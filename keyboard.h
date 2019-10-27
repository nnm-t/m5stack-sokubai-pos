#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>

class Keyboard
{
    static constexpr const uint8_t enable_pin = 5;
    static constexpr const uint8_t i2c_address = 0x08;
    static constexpr const uint8_t request_bytes = 1;

protected:
    virtual void ReceiveKeyCode(uint8_t code);

public:
    Keyboard()
    {

    }

    void Begin();

    void Update();
};