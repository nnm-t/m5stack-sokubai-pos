#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "goods-list.h"
#include "lcd.h"
#include "vector2.h"
#include "constants.h"
#include "state-selector.h"

class GoodsState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr const Vector2<int32_t> left_tr0 = Vector2<int32_t>(30, 105);
    static constexpr const Vector2<int32_t> left_tr1 = Vector2<int32_t>(10, 120);
    static constexpr const Vector2<int32_t> left_tr2 = Vector2<int32_t>(30, 135);

    static constexpr const Vector2<int32_t> right_tr0 = Vector2<int32_t>(290, 105);
    static constexpr const Vector2<int32_t> right_tr1 = Vector2<int32_t>(310, 120);
    static constexpr const Vector2<int32_t> right_tr2 = Vector2<int32_t>(290, 135);

    StateSelector* const _selector;

    GoodsList* const _goods_list;

public:
    GoodsState(StateSelector* const selector, GoodsList* const goods_list) : _selector(selector), _goods_list(goods_list)
    {

    }

    FooterText GetFooterText() override;

    void Begin() override;

    void Update() override;

    void Draw() override;

    void Up() override;

    void Down() override;

    void Left() override;

    void Right() override;

    void Select() override;

    void Start() override;

    void GameboyA() override
    {
        Up();
    }

    void GameboyB() override
    {
        Down();
    }

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    void RFIDReceived(const std::vector<byte>& uuid);

    void WriteSales() override;
};