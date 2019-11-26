#include "header.h"

constexpr Rect<int32_t> Header::background_rect;
constexpr Rect<int32_t> Header::battery_rect;

constexpr Vector2<int32_t> Header::background_pos;

constexpr Vector2<int32_t> Header::circle_pos;

constexpr Vector2<int32_t> Header::battery_pos;
constexpr Vector2<int32_t> Header::battery_rect_pos;

constexpr Vector2<int32_t> Header::connected_pos;

void Header::Draw()
{
    const bool is_ready = _serial->IsReady();
    DrawConnected(is_ready);

    const int8_t battery_level = Power::GetBatteryLevel();
    DrawBatteryLevel(battery_level);
}

void Header::DrawConnected(const bool is_ready)
{
    if (is_ready == _is_ready)
    {
        return;
    }

    _is_ready = is_ready;

    LCD::FillRect(background_pos, background_rect, color_white);

    String connected;

    if (_is_ready)
    {
        LCD::FillCircle(circle_pos, circle_radius, color_bluetooth);

        LCD::SetTextColor(color_bluetooth, color_white);
        connected = "Bluetooth";
    }
    else
    {
        LCD::SetTextColor(color_black, color_white);
        connected = "No Connection";
    }

    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString(connected, connected_pos);
}

void Header::DrawBatteryLevel(const int8_t battery_level)
{
    if (battery_level == _battery_level)
    {
        return;
    }

    _battery_level = battery_level;

    if (_battery_level > battery_high)
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_green);
        LCD::SetTextColor(color_white, color_green);
    } 
    else if (_battery_level > battery_medium)
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_orange);
        LCD::SetTextColor(color_white, color_orange);
    }
    else if (_battery_level > battery_low)
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_red);
        LCD::SetTextColor(color_white, color_red);
    }
    else
    {
        LCD::FillRect(battery_rect_pos, battery_rect, color_black);
        LCD::SetTextColor(color_white, color_black);
    }

    LCD::SetTextDatum(TextDatum::TopRight);
    LCD::DrawString(String(_battery_level) + "%", battery_pos);
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