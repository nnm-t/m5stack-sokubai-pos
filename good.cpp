#include "good.h"

constexpr Vector2<uint16_t> Good::image_pos;
constexpr Vector2<int32_t> Good::name_pos;
constexpr Vector2<int32_t> Good::price_pos;
constexpr Vector2<int32_t> Good::qty_pos;

Good Good::Deserialize(JsonVariant& json)
{
    String name = json[json_name].as<String>();
    String image_path = json[json_image].as<String>();
    uint32_t price = json[json_price].as<uint32_t>();

    return Good(name, image_path, price);
}

void Good::Draw()
{
    LCD::DrawBmpFile(image_pos, _image_path);

    LCD::LoadFont(font_20pt);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString(_name, name_pos);

    LCD::DrawString("数量: " + String(_quantity), qty_pos);

    LCD::LoadFont(font_30pt);
    LCD::SetTextColor(color_red, color_black);
    LCD::DrawString(String(_price) + "円", price_pos);
}