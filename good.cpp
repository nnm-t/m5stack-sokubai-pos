#include "good.h"

using namespace std;

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
    int32_t price = json[json_price].as<int32_t>();

    vector<byte> uuid;

    if (json.containsKey(json_uuid))
    {
        JsonArray uuid_array = json[json_uuid].as<JsonArray>();
        uuid.reserve(uuid_array.size());

        for (JsonVariant uuid_byte : uuid_array)
        {
            byte number = uuid_byte.as<byte>();
            uuid.push_back(number);
        }
    }

    return Good(name, image_path, price, uuid);
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
    if (_quantity < quantity_min)
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

const bool Good::IsMatchUUID(const vector<byte>& uuid)
{
    const size_t length = _uuid.size();

    if (length == 0)
    {
        return false;
    }

    if (length != uuid.size())
    {
        return false;
    }

    for (size_t i = 0; i < length; i++)
    {
        if (_uuid[i] != uuid[i])
        {
            return false;
        }
    }

    return true;
}