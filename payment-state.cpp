#include "payment-state.h"

using namespace std;

constexpr Vector2<int32_t> PaymentState::title_pos;
constexpr Vector2<int32_t> PaymentState::amount_left_pos;
constexpr Vector2<int32_t> PaymentState::amount_right_pos;
constexpr Vector2<int32_t> PaymentState::price_left_pos;
constexpr Vector2<int32_t> PaymentState::price_right_pos;

constexpr Vector2<int32_t> PaymentState::goods_bg_pos;

constexpr Rect<int32_t> PaymentState::goods_bg_rect;
constexpr Rect<int32_t> PaymentState::triangle_rect;

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

    _goods_index.clear();

    _page = 0;
    _sum_price = 0;

    vector<Good>& goods = _goods_list->GetGoods();

    for(size_t i = 0; i < GetGoodsSize(); i++)
    {
        int8_t quantity = goods[i].GetQuantity();
        int32_t good_price = goods[i].GetSumPrice();

        if (quantity == 0)
        {
            continue;
        }

        _goods_index.push_back(i);
        _sum_price += good_price;
    }

    DrawGoods();

    int32_t amount_price = _amount_state->GetPrice();

    if (amount_price != 0)
    {
        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString("金額入力", amount_left_pos);
        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(String(amount_price) +  "円", amount_right_pos);

        _sum_price += amount_price;
    }

    LCD::SetTextColor(color_yellow, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("合計", price_left_pos);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(_sum_price) + "円", price_right_pos);
}

void PaymentState::DrawGoods()
{
    LCD::SetTextColor(color_white, color_black);

    LCD::FillRect(goods_bg_pos, goods_bg_rect, color_black);

    LCD::FillRect(Vector2<int32_t>(289, 189), triangle_rect, color_black);
    LCD::FillRect(Vector2<int32_t>(289, 29), triangle_rect, color_black);

    if (_page > 0)
    {
        LCD::FillTriangle(Vector2<int32_t>(290, 50), Vector2<int32_t>(310, 50), Vector2<int32_t>(300, 30), color_red);
    }

    if (_page != GetGoodsPages() - 1)
    {
        LCD::FillTriangle(Vector2<int32_t>(290, 190), Vector2<int32_t>(310, 190), Vector2<int32_t>(300, 210), color_red);
    }

    const size_t index_size = _goods_index.size();

    if (index_size == 0)
    {
        return;
    }

    int32_t y = good_y;

    vector<Good>& goods = _goods_list->GetGoods();

    for (size_t i = 0; i < page_goods; i++)
    {
        const size_t index_i = _page * page_goods + i;

        if (index_i > index_size - 1)
        {
            continue;
        }

        const size_t index = _goods_index[index_i];

        int8_t quantity = goods[index].GetQuantity();
        int32_t good_price = goods[index].GetSumPrice();

        String good_left = goods[index].GetName() + " x" + String(quantity);
        String good_right = String(good_price) + "円";

        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString(good_left, Vector2<int32_t>(good_x_left, y));
        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(good_right, Vector2<int32_t>(good_x_right, y));

        y += good_y_span;
    }
}

void PaymentState::Up()
{
    if (_page <= 0)
    {
        return;
    }

    _page--;

    DrawGoods();
}

void PaymentState::Down()
{
    if (_page >= GetGoodsPages() - 1)
    {
        return;
    }

    _page++;

    DrawGoods();
}

void PaymentState::ButtonA()
{
    // 戻る
    _selector->ToGoodsState();
}

void PaymentState::ButtonC()
{
    // 決定
    // 音を鳴らす
    _speaker->Tone(tone_frequency_hz, tone_duration_ms);
    delay(tone_duration_ms * 2);
    _speaker->Tone(tone_frequency_hz, tone_duration_ms);

    // 支払いを記録
    PrintSales();
    _selector->WriteSales();

    _selector->ToGoodsState();
}

void PaymentState::PrintSales()
{
    _serial->Println("[売上登録]");

    int32_t sum_price = 0;

    for (Good& good : _goods_list->GetGoods())
    {
        int8_t quantity = good.GetQuantity();

        if (quantity == 0)
        {
            return;
        }

        String name = good.GetName();
        int32_t price = good.GetSumPrice();
        sum_price += price;

        _serial->Print(name);
        _serial->Print(" x" + String(quantity));
        _serial->Println(" " + String(price) + "円");
    }

    int32_t amount_price = _amount_state->GetPrice();

    if (amount_price != 0)
    {
        _serial->Println("金額入力: " + String(amount_price) + "円");
    }

    _serial->Println("合計:" + String(sum_price) + "円");
}