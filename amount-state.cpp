#include "amount-state.h"

using namespace std;

constexpr const Vector2<int32_t> AmountState::title_pos;
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
    LCD::FillRect(bg_pos, bg_rect, color_black);

    LCD::SetTextColor(color_white, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("金額入力", title_pos);

    LCD::SetTextDatum(TextDatum::MiddleLeft);
    LCD::DrawString("00円", price_lower_pos);

    DrawPrice();
    DrawPricePlace();
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
    LCD::FillRect(price_rect_pos, price_rect, color_black);
    LCD::SetTextDatum(TextDatum::MiddleRight);
    LCD::DrawString(String(abs((_price % 1000) / 100)), price_100_pos);
    
    if (_price < 0 && _price > -1000)
    {
        LCD::DrawString("-", price_1000_pos);
        return;
    }

    LCD::DrawString(String(_price / 1000), price_1000_pos);
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
    LCD::FillRect(price_place_pos, price_place_rect, color_black);

    if (_price_place == PricePlace::Lower)
    {
        LCD::FillTriangle(price_place_lower0, price_place_lower1, price_place_lower2, color_red);
        return;
    }

    LCD::FillTriangle(price_place_upper0, price_place_upper1, price_place_upper2, color_red);
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