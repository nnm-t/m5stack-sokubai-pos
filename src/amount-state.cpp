#include "amount-state.h"

using namespace std;

constexpr const Vector2<int32_t> AmountState::title_pos;
constexpr const Vector2<int32_t> AmountState::title2_pos;
constexpr const Vector2<int32_t> AmountState::price_1000_pos;
constexpr const Vector2<int32_t> AmountState::price_100_pos;
constexpr const Vector2<int32_t> AmountState::price_lower_pos;

constexpr const Vector2<int32_t> AmountState::price_rect_pos;
constexpr const Vector2<int32_t> AmountState::price_place_pos;

constexpr const Vector2<int32_t> AmountState::price_place_upper0;
constexpr const Vector2<int32_t> AmountState::price_place_upper1;
constexpr const Vector2<int32_t> AmountState::price_place_upper2;

constexpr const Vector2<int32_t> AmountState::price_place_lower0;
constexpr const Vector2<int32_t> AmountState::price_place_lower1;
constexpr const Vector2<int32_t> AmountState::price_place_lower2;

constexpr const Rect<int32_t> AmountState::price_rect;
constexpr const Rect<int32_t> AmountState::price_place_rect;

FooterText AmountState::GetFooterText()
{
    return FooterText("商品入力", "売上", "会計");
}

void AmountState::Draw()
{
    LCD::FillRect(bg_pos, bg_rect, color_background1);

    LCD::SetTextColor(color_foreground, color_background1);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("金額入力", title_pos);
    LCD::DrawString("100円単位で入力して下さい", title2_pos);

    LCD::SetTextDatum(TextDatum::MiddleLeft);
    LCD::SetFont(&fonts::lgfxJapanGothic_32);
    LCD::DrawString("00円", price_lower_pos);

    DrawPrice();
    DrawPricePlace();
}

void AmountState::Deserialize(JsonArray& json_array)
{
    for (JsonVariant json_variant : json_array)
    {
        _amounts.push_back(json_variant.as<int32_t>());
    }
}

void AmountState::Serialize(JsonArray& json_array)
{
    for (int32_t amount : _amounts)
    {
        json_array.add(amount);
    }
}

void AmountState::Up()
{
    if (_price >= price_max)
    {
        return;
    }

    _price += _price_place == PricePlace::Lower ? 100 : 1000;
    DrawPrice();
}

void AmountState::Down()
{
    if (_price <= price_min)
    {
        return;
    }

    _price -= _price_place == PricePlace::Lower ? 100 : 1000;
    DrawPrice();
}

void AmountState::DrawPrice()
{
    LCD::FillRect(price_rect_pos, price_rect, color_background1);
    LCD::SetTextDatum(TextDatum::MiddleRight);
    LCD::SetTextColor(color_foreground, color_background1);
    LCD::SetFont(&fonts::lgfxJapanGothic_32);
    LCD::DrawString(String(abs((_price % 1000) / 100)), price_100_pos);
    
    if (_price < 0 && _price > -1000)
    {
        LCD::DrawString("-", price_1000_pos);
        return;
    }

    LCD::DrawString(String(_price / 1000), price_1000_pos);
    LCD::SetFont(&fonts::lgfxJapanGothic_20);
}

void AmountState::Left()
{
    _price_place = _price_place == PricePlace::Lower ? PricePlace::Upper : PricePlace::Lower;
    DrawPricePlace();
}

void AmountState::Right()
{
    _price_place = _price_place == PricePlace::Upper ? PricePlace::Lower : PricePlace::Upper;
    DrawPricePlace();
}

void AmountState::DrawPricePlace()
{
    LCD::FillRect(price_place_pos, price_place_rect, color_background1);

    if (_price_place == PricePlace::Lower)
    {
        LCD::FillTriangle(price_place_lower0, price_place_lower1, price_place_lower2, color_accent1);
        return;
    }

    LCD::FillTriangle(price_place_upper0, price_place_upper1, price_place_upper2, color_accent1);
}

void AmountState::Select()
{
    _price = 0;
    DrawPrice();
}

void AmountState::ButtonA()
{
    _selector->ToGoodsState();
}

void AmountState::ButtonB()
{
    _selector->ToSalesState();
}

void AmountState::ButtonC()
{
    _selector->ToPaymentState();
}

void AmountState::WriteSales()
{
    if (_price == 0)
    {
        // ゼロ円は入力しない
        return;
    }

    // 売上を追加
    _amounts.push_back(_price);
    // リセット
    _price = 0;
}

const int32_t AmountState::GetSumSales()
{
    int32_t sales = 0;

    for (const int32_t amount : _amounts)
    {
        sales += amount;
    }

    return sales;
}