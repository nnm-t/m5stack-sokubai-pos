#pragma once

#include <functional>
#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

namespace SokubaiPos
{
    using ButtonCallback  = void (*)();

    class M5Button
    {
        Button* _button;

        std::function<void()> _on_pressed;
        std::function<void()> _on_released;

    public:
        M5Button(Button* button)
        : _button(button)
        {
            _on_pressed = nullptr;
        }

        void Loop()
        {
            if (_button->wasPressed())
            {
                if (_on_pressed != nullptr)
                {
                    _on_pressed();
                }
            }

            if (_button->wasReleased())
            {
                if (_on_released != nullptr)
                {
                    _on_released();
                }
            }
        }

        void SetOnPressed(const std::function<void()>& func)
        {
            _on_pressed = func;
        }

        void SetOnReleased(const std::function<void()>& func)
        {
            _on_released = func;
        }
    };
}