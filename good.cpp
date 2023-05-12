#include "good.h"

using namespace std;

constexpr Vector2<uint16_t> Good::image_pos;
constexpr Vector2<int32_t> Good::name_pos;
constexpr Vector2<int32_t> Good::name_line_pos;
constexpr Vector2<int32_t> Good::name_line_end_pos;
constexpr Vector2<int32_t> Good::name_rect_pos;
constexpr Vector2<int32_t> Good::price_title_pos;
constexpr Vector2<int32_t> Good::price_pos;
constexpr Vector2<int32_t> Good::price_rect_pos;
constexpr Vector2<int32_t> Good::qty_pos;
constexpr Vector2<int32_t> Good::qty_num_pos;
constexpr Vector2<int32_t> Good::qty_num_rect_pos;

constexpr Rect<int32_t> Good::name_rect;
constexpr Rect<int32_t> Good::price_bg_rect;
constexpr Rect<int32_t> Good::qty_bg_rect;

Good Good::Deserialize(JsonVariant& good, JsonVariant& sales)
{
    String name = good[json_name].as<String>();
    String image_path = good[json_image].as<String>();
    int32_t price = good[json_price].as<int32_t>();

    int16_t sales_num = sales.as<int16_t>();

    vector<byte> uuid;

    if (good.containsKey(json_uuid))
    {
        JsonArray uuid_array = good[json_uuid].as<JsonArray>();
        uuid.reserve(uuid_array.size());

        for (JsonVariant uuid_byte : uuid_array)
        {
            byte number = uuid_byte.as<byte>();
            uuid.push_back(number);
        }
    }

    return Good(name, image_path, sales_num, price, uuid);
}

int16_t Good::Serialize()
{
    return _sales;
}

void Good::UpdateQuantity()
{
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_foreground, color_background1);

    LCD::FillRect(qty_num_rect_pos, qty_bg_rect, color_background1);
    LCD::DrawString("数量", qty_pos);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(_quantity) + "個", qty_num_pos);
    LCD::SetTextDatum(TextDatum::TopLeft);
}

void Good::Draw()
{
    LCD::DrawBmpFile(image_pos, _image_path);

    DrawName();

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_accent1, color_background1);
    LCD::FillRect(price_rect_pos, price_bg_rect, color_background1);
    LCD::DrawString("単価", price_title_pos);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(_price) + "円", price_pos);
    LCD::SetTextDatum(TextDatum::TopLeft);

    UpdateQuantity();
}

void Good::DrawName()
{
    LCD::FillRect(name_rect_pos, name_rect, color_background1);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_foreground, color_background1);
    LCD::DrawString(_name, name_pos);
    LCD::DrawLine(name_line_pos, name_line_end_pos, color_foreground);
}

void Good::Update()
{
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

void Good::WriteSales()
{
    // 売上を追加
    _sales += _quantity;
    // リセット
    _quantity = 0;
}