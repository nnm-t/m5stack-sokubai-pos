#include "sales-state.h"

constexpr const Vector2<int32_t> SalesState::title_pos;

constexpr const Vector2<int32_t> SalesState::amount_left_pos;
constexpr const Vector2<int32_t> SalesState::amount_right_pos;
constexpr const Vector2<int32_t> SalesState::price_left_pos;
constexpr const Vector2<int32_t> SalesState::price_right_pos;

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

    int32_t y = good_y;
    int32_t sum_price = 0;

    for (Good& good : _goods_list->GetGoods())
    {
        int16_t sales = good.GetSales();
        int32_t good_price = good.GetSumSales();

        if (sales == 0)
        {
            continue;
        }

        String good_left = good.GetName() + " x" + String(sales);
        String good_right = String(good_price) + "円";

        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString(good_left, Vector2<int32_t>(good_x_left, y));

        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(good_right, Vector2<int32_t>(good_x_right, y));

        y += good_y_span;
        sum_price += good_price;
    }

    int32_t amount_sales = _amount_state->GetSumSales();

    if (amount_sales != 0)
    {
        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString("金額入力", amount_left_pos);
        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(String(amount_sales) + "円", amount_right_pos);

        sum_price += amount_sales;
    }

    LCD::SetTextColor(color_yellow, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("合計", price_left_pos);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(sum_price) + "円", price_right_pos);
}

void SalesState::ButtonA()
{
    _selector->ToGoodsState();
}

void SalesState::ButtonB()
{
    _selector->ToAmountState();
}