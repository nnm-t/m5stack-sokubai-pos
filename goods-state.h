#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "state-base.h"
#include "goods-list.h"
#include "lcd.h"
#include "vector2.h"
#include "constants.h"

class GoodsState : public StateBase
{
    static constexpr const Vector2<int32_t> left_tr0 = Vector2<int32_t>(30, 105);
    static constexpr const Vector2<int32_t> left_tr1 = Vector2<int32_t>(10, 120);
    static constexpr const Vector2<int32_t> left_tr2 = Vector2<int32_t>(30, 135);

    static constexpr const Vector2<int32_t> right_tr0 = Vector2<int32_t>(290, 105);
    static constexpr const Vector2<int32_t> right_tr1 = Vector2<int32_t>(310, 120);
    static constexpr const Vector2<int32_t> right_tr2 = Vector2<int32_t>(290, 135);

    GoodsList* _goods_list;

public:
    GoodsState(GoodsList* goods_list) : _goods_list(goods_list)
    {

    }

    void Begin() override;

    void Draw() override;

    void Loop() override;

    void Up();

    void Down();

    void Left();

    void Right();

    void Select();
};