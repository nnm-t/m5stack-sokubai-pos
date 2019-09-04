#pragma once

#include <functional>

#include <Arduino.h>
#include <M5Stack.h>

#include "../sokubai-pos.h"

namespace SokubaiPos
{
    class StateBase
    {
        M5Button _button_a;
        M5Button _button_b;
        M5Button _button_c;

    public:
        StateBase()
        : _button_a(M5Button(&M5.BtnA)), _button_b(M5Button(&M5.BtnB)), _button_c(M5Button(&M5.BtnC))
        {
            std::function<void()> a_pressed = [this]{ OnButtonAPressed(); };
            std::function<void()> b_pressed = [this]{ OnButtonAPressed(); };
            std::function<void()> c_pressed = [this]{ OnButtonAPressed(); };

            _button_a.SetOnPressed(a_pressed);
            _button_b.SetOnPressed(b_pressed);
            _button_c.SetOnPressed(c_pressed);
        }

        void Loop()
        {
            _button_a.Loop();
            _button_b.Loop();
            _button_c.Loop();
        }

        virtual void OnLoad() = 0;

        virtual void OnButtonAPressed()
        {

        }

        virtual void OnButtonBPressed()
        {

        }

        virtual void OnButtonCPressed()
        {

        }
    };
}