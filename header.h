#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "rect.h"
#include "text-datum.h"
#include "power.h"
#include "diagram.h"
#include "text.h"
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

        void Begin();
    };
}