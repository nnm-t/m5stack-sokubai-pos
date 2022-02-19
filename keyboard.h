#pragma once

#include <functional>

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
    std::function<void()> on_up_pressed = nullptr;
    std::function<void()> on_down_pressed = nullptr;
    std::function<void()> on_left_pressed = nullptr;
    std::function<void()> on_right_pressed = nullptr;
    std::function<void()> on_a_pressed = nullptr;
    std::function<void()> on_b_pressed = nullptr;
    std::function<void()> on_start_pressed = nullptr;
    std::function<void()> on_select_pressed = nullptr;
    std::function<void()> on_released = nullptr;

    Keyboard()
    {

    }

    void Begin();

    void Update();
};