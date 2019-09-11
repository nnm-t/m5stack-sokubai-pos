#include "header.h"

namespace SokubaiPos
{
    void Header::Begin()
    {
        _diagram.FillRect(pos, rect, color_black);

        _battery_text.LoadFont(font_20pt);
        _battery_text.Draw(GetBatteryLevel() + "%", battery_pos);
    }
}