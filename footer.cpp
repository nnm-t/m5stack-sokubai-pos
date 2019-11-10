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

void Footer::Draw(const FooterText& footer_text)
{
    LCD::LoadFont(font_20pt);

    LCD::FillRect(background_pos, background_rect, color_white);

    LCD::SetTextDatum(TextDatum::TopCenter);
    LCD::SetTextColor(color_black, color_white);

    LCD::DrawString(footer_text.GetLeft(), left_text_pos);
    LCD::DrawString(footer_text.GetCenter(), center_text_pos);
    LCD::DrawString(footer_text.GetRight(), right_text_pos);

    LCD::DrawRect(left_pos, border_rect, color_black);
    LCD::DrawRect(center_pos, border_rect, color_black);
    LCD::DrawRect(right_pos, border_rect, color_black);

}