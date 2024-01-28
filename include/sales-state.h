#pragma once

#include <vector>
#include <unordered_map>

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "footer-text.h"
#include "state-selector.h"
#include "amount-state.h"
#include "goods-list.h"
#include "good.h"
#include "i-serial.h"

class SalesState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr const int32_t good_x_left = 10;
    static constexpr const int32_t good_x_right = 310;
    static constexpr const int32_t good_y = 60;
    static constexpr const int32_t good_y_span = 20;

    static constexpr const int32_t amount_y = 160;
    static constexpr const int32_t price_y = 190;

    static constexpr const size_t page_values = 5;

    static constexpr const Vector2<int32_t> amount_left_pos = Vector2<int32_t>(good_x_left, amount_y);
    static constexpr const Vector2<int32_t> amount_right_pos = Vector2<int32_t>(good_x_right, amount_y);

    static constexpr const Vector2<int32_t> price_left_pos = Vector2<int32_t>(good_x_left, price_y);
    static constexpr const Vector2<int32_t> price_right_pos = Vector2<int32_t>(280, price_y);
    static constexpr const Vector2<int32_t> price_line_left_pos = Vector2<int32_t>(good_x_left, 210);
    static constexpr const Vector2<int32_t> price_line_right_pos = Vector2<int32_t>(280, 210);

    static constexpr const Vector2<int32_t> bg_list_pos = Vector2<int32_t>(0, 30);
    static constexpr const Rect<int32_t> bg_list_rect = Rect<int32_t>(320, 160);

    static constexpr const Vector2<int32_t> bg_list_pos2 = Vector2<int32_t>(good_x_left, good_y);
    static constexpr const Rect<int32_t> bg_list_rect2 = Rect<int32_t>(good_x_right - good_x_left, good_y_span * 5);

    static constexpr const Rect<int32_t> triangle_rect = Rect<int32_t>(22, 22);

    StateSelector* const _selector;
    AmountState* const _amount_state;
    GoodsList* const _goods_list;
    ISerial* const _serial;

    bool _is_amount = false;
    size_t _page = 0;
    size_t _max_page = 0;

    std::unordered_map<int32_t, int16_t> _amounts;

    const size_t GetGoodsSize()
    {
        return _goods_list->GetGoods().size();
    }

    const size_t GetGoodsPages()
    {
        return GetGoodsSize() / page_values + 1;
    }

    const size_t GetAmountsPages()
    {
        return _amounts.size() / page_values + 1;
    }

    const size_t GetMaxPages();

    void PrintSales();

    void DrawGoods();

    void DrawAmounts();

    void DrawBody();

    void DrawTriangle();

public:
    SalesState(StateSelector* const selector, AmountState* const amount_state, GoodsList* const goods_list, ISerial* const serial) : _selector(selector), _amount_state(amount_state), _goods_list(goods_list), _serial(serial), _amounts(std::unordered_map<int32_t, int16_t>())
    {

    }

    FooterText GetFooterText() override;

    void Begin() override
    {

    }

    void Update() override
    {

    }

    void Draw() override;

    void Up() override;

    void Down() override;

    void Left() override
    {

    }

    void Right() override
    {

    }

    void Select() override
    {

    }

    void Start() override
    {

    }

    void GameboyA() override
    {
        ButtonC();
    }

    void GameboyB() override
    {
        ButtonA();
    }

    void GameboyReleased() override
    {

    }

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    void WriteSales() override
    {

    }
};