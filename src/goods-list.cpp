#include "goods-list.h"

using namespace std;

constexpr Vector2<int32_t> GoodsList::sum_title_pos;
constexpr Vector2<int32_t> GoodsList::sum_pos;
constexpr Vector2<int32_t> GoodsList::sum_rect_pos;
constexpr Vector2<int32_t> GoodsList::sum_line_start_pos;
constexpr Vector2<int32_t> GoodsList::sum_line_end_pos;

constexpr Rect<int32_t> GoodsList::sum_rect;
constexpr Rect<int16_t> GoodsList::name_rect;

void GoodsList::Deserialize(JsonArray& json_goods, JsonArray& json_sales)
{
    for (size_t i = 0; i < json_goods.size(); i++)
    {
        JsonVariant goods = json_goods[i];
        JsonVariant sales = json_sales[i];
        _goods.push_back(Good::Deserialize(goods, sales));
    }
}

void GoodsList::Serialize(JsonArray& json_array)
{
    for (Good& good : _goods)
    {
        json_array.add(good.Serialize());
    }
}

void GoodsList::Begin()
{
    Draw();
}

void GoodsList::Draw()
{
    _goods[_current].Draw();
    DrawSumPrice();
}

void GoodsList::Update()
{
    if (_goods.size() < 1)
    {
        return;
    }

    _goods[_current].Update();
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
    int16_t num = 0;
    int32_t sum = 0;

    for (uint16_t n : GetQuantities())
    {
        num += n;
    }

    for (Good& good : _goods)
    {
        sum += good.GetSumPrice();
    }

    LCD::SetTextColor(color_accent2, color_background1);
    LCD::SetTextDatum(TextDatum::TopLeft);

    LCD::FillRect(sum_rect_pos, sum_rect, color_background1);
    LCD::DrawString("合計", sum_title_pos);
    LCD::DrawLine(sum_line_start_pos, sum_line_end_pos, color_accent2);
    LCD::SetFont(&fonts::lgfxJapanGothic_32);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(sum) + "円", sum_pos);
    LCD::SetFont(&fonts::lgfxJapanGothic_20);
    LCD::SetTextDatum(TextDatum::TopLeft);
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

            _goods[i].Draw();
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

vector<String> GoodsList::GetNames()
{
    vector<String> names;
    names.reserve(_goods.size());

    for (Good& good : _goods)
    {
        names.push_back(good.GetName());
    }
    
    return names;
}

vector<int16_t> GoodsList::GetQuantities()
{
    vector<int16_t> quantities;
    quantities.reserve(_goods.size());

    for (Good& good : _goods)
    {
        quantities.push_back(good.GetQuantity());
    }

    return quantities;
}