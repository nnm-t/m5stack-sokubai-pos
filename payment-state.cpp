#include "payment-state.h"

constexpr Vector2<int32_t> PaymentState::title_pos;
constexpr Vector2<int32_t> PaymentState::amount_left_pos;
constexpr Vector2<int32_t> PaymentState::amount_right_pos;
constexpr Vector2<int32_t> PaymentState::price_left_pos;
constexpr Vector2<int32_t> PaymentState::price_right_pos;

FooterText PaymentState::GetFooterText()
{
    return FooterText("戻る", String(), "決定");
}

void PaymentState::Draw()
{
    LCD::FillRect(bg_pos, bg_rect, color_black);

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("支払", title_pos);

    int32_t y = good_y;
    int32_t sum_price = 0;

    for(Good& good : _goods_list->GetGoods())
    {
        // todo: スクロール
        int8_t quantity = good.GetQuantity();
        int32_t good_price = good.GetSumPrice();

        if (quantity == 0)
        {
            continue;
        }

        String good_left = good.GetName() + " x" + String(quantity);
        String good_right = String(good_price) + "円";

        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString(good_left, Vector2<int32_t>(good_x_left, y));
        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(good_right, Vector2<int32_t>(good_x_right, y));
        y += good_y_span;
        sum_price += good_price;
    }

    int32_t amount_price = _amount_state->GetPrice();

    if (amount_price != 0)
    {
        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString("金額入力", amount_left_pos);
        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(String(amount_price) +  "円", amount_right_pos);

        sum_price += amount_price;
    }

    LCD::SetTextColor(color_yellow, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("合計", price_left_pos);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(sum_price) + "円", price_right_pos);
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
    _selector->WriteSales();

    _selector->ToGoodsState();
}