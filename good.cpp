#include "good.h"

namespace SokubaiPos
{
    void Good::IncrementQuantity()
    {
        _qty++;
    }

    void Good::DecrementQuantity()
    {
        _qty--;
    }

    void Good::Draw()
    {
        LCD::DrawBitmapFile(_image_path.c_str(), image_pos);

        Text price_text(30, color_black, color_white);
        price_text.LoadFont(font_30pt);
        price_text.Draw(_name, price_pos);

        Text qty_text(20, color_black, color_white);
        qty_text.LoadFont(font_20pt);
        qty_text.Draw("数量: " + String(_qty), qty_pos);
    }
}