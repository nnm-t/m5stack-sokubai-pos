#include "good.h"

constexpr Vector2<uint16_t> Good::image_pos;
constexpr Vector2<int32_t> Good::name_pos;
constexpr Vector2<int32_t> Good::price_pos;
constexpr Vector2<int32_t> Good::qty_pos;

constexpr Rect<int32_t> Good::price_bg_rect;
constexpr Rect<int32_t> Good::qty_bg_rect;

Good Good::Deserialize(JsonVariant& json)
{
    String name = json[json_name].as<String>();
    String image_path = json[json_image].as<String>();
    uint32_t price = json[json_price].as<uint32_t>();

    return Good(name, image_path, price);
}

void Good::UpdateQuantity()
{
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);

    LCD::FillRect(qty_pos, qty_bg_rect, color_black);
    LCD::DrawString("数量: " + String(_quantity), qty_pos);
}

void Good::Draw()
{
    LCD::DrawBmpFile(image_pos, _image_path);

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString(_name, name_pos);

    LCD::SetTextColor(color_red, color_black);
    LCD::FillRect(price_pos, price_bg_rect, color_black);
    LCD::DrawString("単価: " + String(_price) + "円", price_pos);

    UpdateQuantity();
}

void Good::Up()
{
    if (_quantity >= quantity_max)
    {
        return;
    }

    _quantity++;

    UpdateQuantity();
}

void Good::Down()
{
    if (_quantity < 1)
    {
        return;
    }

    _quantity--;

    UpdateQuantity();
}

void Good::Reset()
{
    _quantity = 0;
    UpdateQuantity();
}