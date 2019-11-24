#include "goods-list.h"

using namespace std;

constexpr Vector2<int32_t> GoodsList::sum_pos;
constexpr Vector2<int32_t> GoodsList::sum_rect_pos;

constexpr Rect<int32_t> GoodsList::sum_rect;
constexpr Rect<int16_t> GoodsList::name_rect;

void GoodsList::BeginSprite()
{
    _sprite->Create(name_rect);
    _sprite->LoadFont(font_20pt);
    _sprite->SetTextDatum(TextDatum::TopLeft);
    _sprite->SetTextColor(color_white);
}

void GoodsList::Deserialize(JsonArray& json_array)
{
    for (JsonVariant json_variant : json_array)
    {
        _goods.push_back(Good::Deserialize(json_variant));
    }
}

void GoodsList::Serialize(JsonArray& json_array)
{
    for (Good& good : _goods)
    {
        JsonVariant json_variant = json_array.createNestedObject();
        good.Serialize(json_variant);
    }
}

void GoodsList::Begin()
{
    BeginSprite();

    Draw();
}

void GoodsList::Draw()
{
    if (_goods.size() < 1)
    {
        return;
    }

    _goods[_current].Draw(_sprite);
    DrawSumPrice();
}

void GoodsList::Update()
{
    if (_goods.size() < 1)
    {
        return;
    }

    _goods[_current].Update(_sprite);
}

void GoodsList::Next()
{
    if (_current >= GetLastIndex())
    {
        _current = 0;
    }
    else
    {
        _current++;
    }

    Draw();
}

void GoodsList::Prev()
{
    if (_current <= 0)
    {
        _current = GetLastIndex();
    }
    else
    {
        _current--;
    }

    Draw();
}

void GoodsList::Up()
{
    _goods[_current].Up();
    DrawSumPrice();
}

void GoodsList::Down()
{
    _goods[_current].Down();
    DrawSumPrice();
}

void GoodsList::DrawSumPrice()
{
    int32_t sum = 0;

    for (Good& good : _goods)
    {
        sum += good.GetSumPrice();
    }

    LCD::SetTextColor(color_yellow, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);

    LCD::FillRect(sum_rect_pos, sum_rect, color_black);
    LCD::DrawString("合計: " + String(sum) + "円", sum_pos);
}

void GoodsList::Reset()
{
    for (Good& good : _goods)
    {
        good.Reset();
    }

    DrawSumPrice();
}

void GoodsList::RFIDReceived(const vector<byte>& uuid)
{
    for (size_t i = 0; i < _goods.size(); i++)
    {
        if (_goods[i].IsMatchUUID(uuid))
        {
            _current = i;

            _goods[i].Draw(_sprite);
            _goods[i].Up();
            DrawSumPrice();

            return;
        }
    }
}

void GoodsList::WriteSales()
{
    for (Good& good : _goods)
    {
        good.WriteSales();
    }
}