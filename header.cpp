#include "header.h"

namespace SokubaiPos
{
    constexpr Rect<int32_t> Header::rect;
    constexpr Vector2<int32_t> Header::pos;
    constexpr Vector2<int32_t> Header::battery_pos;

    void Header::Begin()
    {
        _diagram.FillRect(pos, rect, color_black);

        _battery_text.LoadFont(font_20pt);
        _battery_text.Draw(GetBatteryLevel() + "%", battery_pos);
    }
}