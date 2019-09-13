#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "color16.h"
#include "state-base.h"
#include "json-goods.h"
#include "text.h"
#include "diagram.h"

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

        void OnLoad() override;
    };
}