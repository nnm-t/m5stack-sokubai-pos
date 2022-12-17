#include "sales-state.h"

using namespace std;

constexpr const Vector2<int32_t> SalesState::title_pos;

constexpr const Vector2<int32_t> SalesState::amount_left_pos;
constexpr const Vector2<int32_t> SalesState::amount_right_pos;
constexpr const Vector2<int32_t> SalesState::price_left_pos;
constexpr const Vector2<int32_t> SalesState::price_right_pos;

constexpr const Vector2<int32_t> SalesState::bg_list_pos;
constexpr const Rect<int32_t> SalesState::bg_list_rect;

constexpr const Rect<int32_t> SalesState::triangle_rect;

FooterText SalesState::GetFooterText()
{
    if (_is_amount)
    {
        return FooterText("戻る", "商品売上", "送信");
    }

    return FooterText("戻る", "額入売上", "送信");
}

const size_t SalesState::GetMaxPages()
{
    if (_is_amount)
    {
        return GetAmountsPages();
    }

    return GetGoodsPages();
}

void SalesState::DrawTriangle()
{
    LCD::FillRect(Vector2<int32_t>(289, 189), triangle_rect, color_black);
    LCD::FillRect(Vector2<int32_t>(289, 29), triangle_rect, color_black);

    if (_page > 0)
    {
        // 上向き
        LCD::FillTriangle(Vector2<int32_t>(290, 50), Vector2<int32_t>(310, 50), Vector2<int32_t>(300, 30), color_red);
    }

    if (_page != GetMaxPages() - 1)
    {
        // 下向き
        LCD::FillTriangle(Vector2<int32_t>(290, 190), Vector2<int32_t>(310, 190), Vector2<int32_t>(300, 210), color_red);
    }
}

void SalesState::DrawGoods()
{
    LCD::FillRect(bg_list_pos, bg_list_rect, color_black);

    DrawTriangle();

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("商品売上", title_pos);

    int32_t y = good_y;
    vector<Good> goods = _goods_list->GetGoods();

    for (size_t i = 0; i < page_values; i++)
    {
        const size_t index = _page * page_values + i;

        if (index > GetGoodsSize() - 1)
        {
            return;
        }

        int16_t sales = goods[index].GetSales();
        int32_t good_price = goods[index].GetSumSales();

        String good_left = goods[index].GetName() + " x" + String(sales);
        String good_right = String(good_price) + "円";

        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString(good_left, Vector2<int32_t>(good_x_left, y));

        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(good_right, Vector2<int32_t>(good_x_right, y));

        y += good_y_span;
    }
}

void SalesState::DrawAmounts()
{
    LCD::FillRect(bg_list_pos, bg_list_rect, color_black);

    DrawTriangle();

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("金額入力売上", title_pos);

    // unordered_map の途中からの iterate
    auto iterator = _amounts.begin();
    int32_t y = good_y;

    // 予め iterator を動かす
    for (size_t i = 0; i < _page * page_values; i++)
    {
        iterator++;
    }

    for (size_t i = 0; i < page_values; i++)
    {
        if (iterator == _amounts.end())
        {
            return;
        }

        const int32_t unit_price = iterator->first;
        const int16_t quantity = iterator->second;
        const int32_t amount_price = unit_price * quantity;

        String amount_left = String(unit_price) + "円 x" + String(quantity);
        String amount_right = String(amount_price) + "円";

        LCD::SetTextDatum(TextDatum::TopLeft);
        LCD::DrawString(amount_left, Vector2<int32_t>(good_x_left, y));
        LCD::SetTextDatum(TextDatum::TopRight);
        LCD::DrawString(amount_right, Vector2<int32_t>(good_x_right, y));

        iterator++;
        y += good_y_span;
    }
}

void SalesState::DrawBody()
{
    if (_is_amount)
    {
        DrawAmounts();
        return;
    }

    DrawGoods();
}

void SalesState::Draw()
{
    LCD::FillRect(bg_pos, bg_rect, color_black);

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

        sum_price += good_price;
    }

    sum_price += _amount_state->GetSumSales();

    _amounts.clear();

    // unordered_map へ抽出
    for (const int32_t amount : _amount_state->GetAmounts())
    {
        if (_amounts.find(amount) != _amounts.end())
        {
            _amounts[amount]++;
            continue;
        }

        _amounts[amount] = 1;
    }

    LCD::SetTextColor(color_yellow, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("合計", price_left_pos);
    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(sum_price) + "円", price_right_pos);

    DrawBody();
}

void SalesState::ButtonA()
{
    _selector->ToGoodsState();
}

void SalesState::ButtonB()
{
    _is_amount = !_is_amount;
    _page = 0;
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

    for (auto& amount : _amounts)
    {
        const int32_t price = amount.first * amount.second;

        _serial->Print(String(amount.first) + "円");
        _serial->Print(" x" + String(amount.second));
        _serial->Println(" " + String(price) + "円");

        sum_price += price;
    }

    _serial->Print("合計: " + String(sum_price) + "円");
}

void SalesState::Up()
{
    if (_page <= 0)
    {
        return;
    }

    _page--;

    DrawBody();
}

void SalesState::Down()
{
    if (_page >= GetMaxPages() - 1)
    {
        return;
    }

    _page++;

    DrawBody();
}