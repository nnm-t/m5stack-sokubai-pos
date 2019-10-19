#include "header.h"

constexpr Rect<int32_t> Header::background_rect;

constexpr Vector2<int32_t> Header::background_pos;
constexpr Vector2<int32_t> Header::battery_pos;
constexpr Vector2<int32_t> Header::wifi_pos;

void Header::Draw()
{
    LCD::FillRect(background_pos, background_rect, color_black);

    LCD::LoadFont(font_20pt);

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString(WiFi.macAddress(), wifi_pos);

    LCD::SetTextDatum((TextDatum::TopRight));
    LCD::DrawString(Power::GetBatteryLevel() + "%", battery_pos);
}