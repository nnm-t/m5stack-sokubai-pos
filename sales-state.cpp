#include "sales-state.h"

constexpr const Vector2<int32_t> SalesState::title_pos;

constexpr const Vector2<int32_t> SalesState::amount_left_pos;
constexpr const Vector2<int32_t> SalesState::amount_right_pos;
constexpr const Vector2<int32_t> SalesState::price_left_pos;
constexpr const Vector2<int32_t> SalesState::price_right_pos;

FooterText SalesState::GetFooterText()
{
    if (_is_amount)
    {
        return FooterText("戻る", "商品売上", "送信");
    }

    return FooterText("戻る", "額入売上", "送信");
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
        // todo: スクロール
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
        // todo: 金額ごとカウントに変更
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
    _is_amount = !_is_amount;
    _selector->ToSalesState();
}

void SalesState::ButtonC()
{
    PrintSales();
}

void SalesState::PrintSales()
{
    int32_t sum_price = 0;

    _serial->Println("[売上累計]");

    for (Good& good : _goods_list->GetGoods())
    {
        int16_t sales = good.GetSales();

        if (sales == 0)
        {
            continue;
        }

        String name = good.GetName();
        int32_t amount_sales = good.GetSumSales();

        _serial->Print(name);
        _serial->Print(" x" + String(sales));
        _serial->Println(" " + String(amount_sales) + "円");

        sum_price += amount_sales;
    }

    // todo: 金額入力
}