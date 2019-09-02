#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "constants.h"
#include "sokubai-pos.h"

namespace SokubaiPos
{
    class Header
    {
        const Rect<int32_t> _rect = Rect<int32_t>(320, 20);
        const uint8_t _font_size = 20;
        const Color16 _background = Color16::From32(0x000000);
        const Color16 _foreground = Color16::From32(0xFFFFFF);

        const Vector2<int32_t> _pos = Vector2<int32_t>::Zero();
        const Vector2<int32_t> _battery_text_pos = Vector2<int32_t>(320, 0);

        Diagram _diagram;
        Text _battery_text;

        String GetBatteryLevel()
        {
            return String(Power::GetBatteryLevel());
        }

    public:
        Header()
        : _diagram(Diagram()),
         _battery_text(_font_size, _foreground, _background, TextDatum::TopRight)
        {

        }

        void Begin()
        {
            _diagram.FillRect(_pos, _rect, _background);

            _battery_text.LoadFont(font_20pt);
            _battery_text.Draw(GetBatteryLevel() + "%", _battery_text_pos);
        }
    };
}