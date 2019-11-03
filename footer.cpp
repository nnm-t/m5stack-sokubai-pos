#include "footer.h"

constexpr Rect<int32_t> Footer::background_rect;
constexpr Rect<int32_t> Footer::border_rect;

constexpr Vector2<int32_t> Footer::background_pos;
constexpr Vector2<int32_t> Footer::left_pos;
constexpr Vector2<int32_t> Footer::center_pos;
constexpr Vector2<int32_t> Footer::right_pos;

constexpr Vector2<int32_t> Footer::left_text_pos;
constexpr Vector2<int32_t> Footer::center_text_pos;
constexpr Vector2<int32_t> Footer::right_text_pos;

void Footer::Draw()
{
    LCD::FillRect(background_pos, background_rect, color_white);

    LCD::SetTextDatum(TextDatum::TopCenter);
    LCD::SetTextColor(color_black, color_white);

    LCD::DrawString("反転", left_text_pos);
    LCD::DrawString("金額入力", center_text_pos);
    LCD::DrawString("会計", right_text_pos);

    LCD::DrawRect(left_pos, border_rect, color_black);
    LCD::DrawRect(center_pos, border_rect, color_black);
    LCD::DrawRect(right_pos, border_rect, color_black);

}