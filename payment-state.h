#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "state-selector.h"
#include "amount-state.h"
#include "goods-list.h"
#include "footer-text.h"
#include "constants.h"
#include "lcd.h"
#include "vector2.h"
#include "text-datum.h"

class PaymentState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr const int32_t good_x_left = 10;
    static constexpr const int32_t good_x_right = 310;
    static constexpr const int32_t good_y = 60;
    static constexpr const int32_t good_y_span = 20;

    static constexpr const int32_t amount_y = 160;
    static constexpr const int32_t price_y = 190;

    static constexpr const Vector2<int32_t> amount_left_pos = Vector2<int32_t>(good_x_left, amount_y);
    static constexpr const Vector2<int32_t> amount_right_pos = Vector2<int32_t>(good_x_right, amount_y);

    static constexpr const Vector2<int32_t> price_left_pos = Vector2<int32_t>(good_x_left, price_y);
    static constexpr const Vector2<int32_t> price_right_pos = Vector2<int32_t>(good_x_right, price_y);

    StateSelector* const _selector;
    AmountState* const _amount_state;
    GoodsList* const _goods_list;

public:
    PaymentState(StateSelector* const selector, AmountState* const amount_state, GoodsList* const goods_list) : _selector(selector), _amount_state(amount_state), _goods_list(goods_list)
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

    void Up() override
    {

    }

    void Down() override
    {

    }

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

    void ButtonA() override;

    void ButtonB() override
    {

    }

    void ButtonC() override;

    void WriteSales() override
    {

    }
};