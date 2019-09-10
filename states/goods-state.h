#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "../misc/vector2.h"
#include "../m5wrap/color16.h"
#include "state-base.h"

namespace SokubaiPos
{
    class GoodsState : public StateBase
    {
        static constexpr Vector2<int32_t> left_tr0 = Vector2<int32_t>(10, 120);
        static constexpr Vector2<int32_t> left_tr1 = Vector2<int32_t>(30, 100);
        static constexpr Vector2<int32_t> left_tr2 = Vector2<int32_t>(30, 140);

        static constexpr Vector2<int32_t> right_tr0 = Vector2<int32_t>(310, 120);
        static constexpr Vector2<int32_t> right_tr1 = Vector2<int32_t>(290, 100);
        static constexpr Vector2<int32_t> right_tr2 = Vector2<int32_t>(290, 140);

        static constexpr Color16 tr_color = Color16::From32(0xFF0000);

        JsonGoods* _goods;

        Text _text;
        Diagram _diagram;

    public:
        GoodsState(JsonGoods* goods)
         : _goods(goods), _text(Text()), _diagram(Diagram()), StateBase()
        {
        }

        void OnLoad() override
        {
            _diagram.FillTriangle(left_tr0, left_tr1, left_tr2, tr_color);
            _diagram.FillTriangle(right_tr0, right_tr1, right_tr2, tr_color);

            Good* good = _goods->CurrentGood();

            good->Draw();
        }
    };
}