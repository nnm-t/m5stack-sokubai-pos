#include "header.h"

constexpr Rect<int32_t> Header::background_rect;
constexpr Rect<int32_t> Header::battery_rect;

constexpr Vector2<int32_t> Header::background_pos;
constexpr Vector2<int32_t> Header::battery_pos;
constexpr Vector2<int32_t> Header::battery_rect_pos;
constexpr Vector2<int32_t> Header::wifi_pos;

void Header::Draw()
{
    LCD::FillRect(background_pos, background_rect, color_white);

    LCD::SetTextColor(color_black, color_white);

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("ホンナムユーティナイ", wifi_pos);

    const uint8_t battery_level = Power::GetBatteryLevel();
    DrawBatteryLevel(battery_level);

    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(battery_level) + "%", battery_pos);
}

void Header::DrawBatteryLevel(const uint8_t battery_level)
{
    if (battery_level > battery_high)
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_green);
        LCD::SetTextColor(color_white, color_green);
        return;
    }

    if (battery_level > battery_medium)
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_orange);
        LCD::SetTextColor(color_white, color_orange);
        return;
    }

    if (battery_level > battery_low)
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_red);
        LCD::SetTextColor(color_white, color_red);
        return;
    }

    LCD::FillRect(battery_rect_pos, battery_rect, color_black);
    LCD::SetTextColor(color_white, color_black);
}

void Header::Begin()
{
    Draw();
}

void Header::Update()
{
    _period_ms += _delay_ms;

    if (_period_ms < interval_ms)
    {
        return;
    }

    _period_ms = 0;

    Draw();
}