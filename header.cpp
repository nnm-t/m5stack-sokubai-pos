#include "header.h"

constexpr Rect<int32_t> Header::background_rect;
constexpr Rect<int32_t> Header::battery_rect;

constexpr Vector2<int32_t> Header::background_pos;

constexpr Vector2<int32_t> Header::hour_pos;
constexpr Vector2<int32_t> Header::hour_slash_pos;
constexpr Vector2<int32_t> Header::minute_pos;
constexpr Vector2<int32_t> Header::minute_slash_pos;
constexpr Vector2<int32_t> Header::second_pos;

constexpr Vector2<int32_t> Header::battery_pos;
constexpr Vector2<int32_t> Header::battery_rect_pos;

constexpr Vector2<int32_t> Header::connected_pos;

void Header::Draw()
{
    DrawTime();

    const int8_t battery_level = Power::GetBatteryLevel();
    DrawBatteryLevel(battery_level);
}

String Header::Convert2Digit(const uint8_t value)
{
    String str = String(value);

    if (value < 10)
    {
        return String("0" + str);
    }

    return str;
}

void Header::DrawTime()
{
    DateTime time = _rtc->GetNow();

    LCD::FillRect(background_pos, background_rect, color_white);
    LCD::SetTextColor(color_black, color_white);
    LCD::SetTextDatum(TextDatum::TopLeft);

    LCD::DrawString(Convert2Digit(time.hour()), hour_pos);
    LCD::DrawString(":", hour_slash_pos);
    LCD::DrawString(Convert2Digit(time.minute()), minute_pos);
    LCD::DrawString(":", minute_slash_pos);
    LCD::DrawString(Convert2Digit(time.second()), second_pos);

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