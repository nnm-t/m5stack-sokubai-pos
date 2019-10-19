#include "footer.h"

constexpr Rect<int32_t> Footer::background_rect;
constexpr Rect<int32_t> Footer::border_rect;

constexpr Vector2<int32_t> Footer::background_pos;
constexpr Vector2<int32_t> Footer::left_pos;
constexpr Vector2<int32_t> Footer::center_pos;
constexpr Vector2<int32_t> Footer::right_pos;

void Footer::Draw()
{
    LCD::FillRect(background_pos, background_rect, color_black);

    LCD::DrawRect(left_pos, border_rect, color_white);
    LCD::DrawRect(center_pos, border_rect, color_white);
    LCD::DrawRect(right_pos, border_rect, color_white);
}