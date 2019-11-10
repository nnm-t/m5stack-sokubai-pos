#include "payment-state.h"

constexpr Vector2<int32_t> PaymentState::title_pos;
constexpr Vector2<int32_t> PaymentState::amount_pos;

FooterText PaymentState::GetFooterText()
{
    return FooterText("戻る", String(), "決定");
}

void PaymentState::Draw()
{
    LCD::LoadFont(font_20pt);
    LCD::FillRect(bg_pos, bg_rect, color_black);

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("支払", title_pos);

    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::SetTextColor(color_yellow, color_black);
    LCD::DrawString("合計: xxx円", amount_pos);
}

void PaymentState::ButtonA()
{
    // 戻る
    _selector->ToGoodsState();
}

void PaymentState::ButtonC()
{
    // 決定
    // 支払いを記録

    _selector->ToGoodsState();
}