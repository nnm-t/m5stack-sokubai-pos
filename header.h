#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "misc/vector2.h"
#include "misc/rect.h"
#include "m5wrap/text-datum.h"
#include "m5wrap/power.h"
#include "m5wrap/diagram.h"
#include "m5wrap/text.h"
#include "constants.h"

namespace SokubaiPos
{
    class Header
    {
        static constexpr Rect<int32_t> rect = Rect<int32_t>(320, 20);
        static constexpr uint8_t font_size = 20;

        static constexpr Vector2<int32_t> pos = Vector2<int32_t>::Zero();
        static constexpr Vector2<int32_t> battery_pos = Vector2<int32_t>(320, 0);

        Diagram _diagram;
        Text _battery_text;

        String GetBatteryLevel()
        {
            return String(Power::GetBatteryLevel());
        }

    public:
        Header()
        : _diagram(Diagram()),
         _battery_text(font_size, color_white, color_black, TextDatum::TopRight)
        {

        }

        void Begin()
        {
            _diagram.FillRect(pos, rect, color_black);

            _battery_text.LoadFont(font_20pt);
            _battery_text.Draw(GetBatteryLevel() + "%", battery_pos);
        }
    };

    constexpr Rect<int32_t> Header::rect;
    constexpr Vector2<int32_t> Header::pos;
    constexpr Vector2<int32_t> Header::battery_pos;
}