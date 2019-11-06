#pragma once

#include <functional>

#include <Arduino.h>
#include <M5Stack.h>

class M5Button
{
public:
    std::function<void()> on_button_a_pressed = nullptr;
    std::function<void()> on_button_b_pressed = nullptr;
    std::function<void()> on_button_c_pressed = nullptr;

    M5Button()
    {

    }

    void Begin();

    void Update();
};