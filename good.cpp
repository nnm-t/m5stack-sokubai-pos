#include "good.h"

namespace SokubaiPos
{
   constexpr Vector2<uint16_t> Good::image_pos;
   constexpr Vector2<int32_t> Good::name_pos;
   constexpr Vector2<int32_t> Good::price_pos;
   constexpr Vector2<int32_t> Good::qty_pos;

   Good Good::FromJson(JsonVariant& json)
   {
        String name = json["name"].as<String>();
        String image_path = json["image_path"].as<String>();
        uint32_t price = json["price"].as<uint32_t>();

        return Good(price, name, image_path);
   }

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

    uint32_t Good::GetPrice() const
    {
        return _price;
    }

    String Good::GetName() const
    {
        return _name;
    }

    String Good::GetImagePath() const
    {
        return _image_path;
    }

    uint8_t Good::GetQuantity() const
    {
        return _qty;
    }
}