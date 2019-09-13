#include "goods-state.h"

namespace SokubaiPos
{
    constexpr Vector2<int32_t> GoodsState::left_tr0;
    constexpr Vector2<int32_t> GoodsState::left_tr1;
    constexpr Vector2<int32_t> GoodsState::left_tr2;

    constexpr Vector2<int32_t> GoodsState::right_tr0;
    constexpr Vector2<int32_t> GoodsState::right_tr1;
    constexpr Vector2<int32_t> GoodsState::right_tr2;

    constexpr Color16 GoodsState::tr_color;

    void GoodsState::OnLoad()
    {
        _diagram.FillTriangle(left_tr0, left_tr1, left_tr2, tr_color);
        _diagram.FillTriangle(right_tr0, right_tr1, right_tr2, tr_color);

        Good* good = _goods->CurrentGood();

        good->Draw();
    }
}