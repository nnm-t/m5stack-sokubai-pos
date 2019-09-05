#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "../sokubai-pos.h"

namespace SokubaiPos
{
    class GoodsState : public StateBase
    {
        static constexpr Vector2<int32_t> left_tr0 = Vector2<int32_t>(10, 160);
        static constexpr Vector2<int32_t> left_tr1 = Vector2<int32_t>(30, 120);
        static constexpr Vector2<int32_t> left_tr2 = Vector2<int32_t>(30, 200);

        static constexpr Vector2<int32_t> right_tr0 = Vector2<int32_t>(310, 160);
        static constexpr Vector2<int32_t> right_tr1 = Vector2<int32_t>(290, 120);
        static constexpr Vector2<int32_t> right_tr2 = Vector2<int32_t>(290, 200);

        static constexpr Color16 tr_color = Color16::From32(0xFF0000);

        const JsonGoods* _goods;

        Text _text;
        Diagram _diagram;

    public:
        GoodsState(const JsonGoods* goods)
         : _goods(goods), _text(Text()), _diagram(Diagram()), StateBase()
        {
        }

        void OnLoad() override
        {
            _diagram.FillTriangle(left_tr0, left_tr1, left_tr2, tr_color);
            _diagram.FillTriangle(right_tr0, right_tr1, right_tr2, tr_color);
        }
    };
}