#include "sales-state.h"

constexpr const Vector2<int32_t> SalesState::title_pos;

FooterText SalesState::GetFooterText()
{
    return FooterText("商品入力", "金額入力", String());
}

void SalesState::Draw()
{
    LCD::FillRect(bg_pos, bg_rect, color_black);

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("売上", title_pos);
}

void SalesState::ButtonA()
{
    _selector->ToGoodsState();
}

void SalesState::ButtonB()
{
    _selector->ToAmountState();
}