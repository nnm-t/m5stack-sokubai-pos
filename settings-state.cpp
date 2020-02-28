#include "settings-state.h"

constexpr Vector2<int32_t> SettingsState::title_pos;
constexpr Vector2<int32_t> SettingsState::time_title_pos;
constexpr Vector2<int32_t> SettingsState::time_triangle0;
constexpr Vector2<int32_t> SettingsState::time_triangle1;
constexpr Vector2<int32_t> SettingsState::time_triangle2;
constexpr Vector2<int32_t> SettingsState::brightness_triangle0;
constexpr Vector2<int32_t> SettingsState::brightness_triangle1;
constexpr Vector2<int32_t> SettingsState::brightness_triangle2;
constexpr Vector2<int32_t> SettingsState::time_bg_pos;
constexpr Rect<int32_t> SettingsState::time_bg_rect;
constexpr Vector2<int32_t> SettingsState::time_year1000_pos;
constexpr Vector2<int32_t> SettingsState::time_year100_pos;
constexpr Vector2<int32_t> SettingsState::time_year10_pos;
constexpr Vector2<int32_t> SettingsState::time_year1_pos;
constexpr Vector2<int32_t> SettingsState::time_year_slash_pos;
constexpr Vector2<int32_t> SettingsState::time_month_pos;
constexpr Vector2<int32_t> SettingsState::time_month_slash_pos;
constexpr Vector2<int32_t> SettingsState::time_day_pos;
constexpr Vector2<int32_t> SettingsState::time_hour_pos;
constexpr Vector2<int32_t> SettingsState::time_hour_colon_pos;
constexpr Vector2<int32_t> SettingsState::time_minute_pos;
constexpr Vector2<int32_t> SettingsState::time_minute_colon_pos;
constexpr Vector2<int32_t> SettingsState::time_second_pos;
constexpr Vector2<int32_t> SettingsState::brightness_title_pos;
constexpr Vector2<int32_t> SettingsState::brightness_bar_pos;
constexpr Rect<int32_t> SettingsState::brightness_bar_rect;
constexpr Rect<int32_t> SettingsState::brightness_rect;

FooterText SettingsState::GetFooterText()
{
    return FooterText("戻る", String(), "決定");
}

void SettingsState::Begin()
{
    _rtc->Begin();
}

void SettingsState::Draw()
{
    LCD::FillRect(bg_pos, bg_rect, color_black);

    _time = _rtc->GetNow();

    LCD::SetTextColor(color_white, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);

    LCD::DrawString("設定", title_pos);

    DrawModeArrow();

    DrawTime();
    DrawBrightness();
}

void SettingsState::DrawModeArrow()
{
    switch(_mode)
    {
        case SettingsStateMode::Time:
            // 時刻
            LCD::FillTriangle(time_triangle0, time_triangle1, time_triangle2, color_red);
            LCD::FillTriangle(brightness_triangle0, brightness_triangle1, brightness_triangle2, color_black);
        break;
        case SettingsStateMode::Brightness:
            LCD::FillTriangle(time_triangle0, time_triangle1, time_triangle2, color_black);
            // 輝度
            LCD::FillTriangle(brightness_triangle0, brightness_triangle1, brightness_triangle2, color_red);
        break;
        default:
        break;
    }
}

String SettingsState::Convert2Digit(const uint8_t number)
{
    if (number < 10)
    {
        return "0" + String(number, DEC);
    }

    return String(number, DEC);
}

void SettingsState::DrawTime()
{
    LCD::FillRect(time_bg_pos, time_bg_rect, color_black);

    LCD::DrawString("時刻", time_title_pos);

    const uint16_t year = _time.year();
    LCD::DrawString(String(year, DEC), time_year1000_pos);
    LCD::DrawString(String(year % 1000, DEC), time_year100_pos);
    LCD::DrawString(String(year % 100, DEC), time_year10_pos);
    LCD::DrawString(String(year % 10, DEC), time_year1_pos);
    LCD::DrawString("/", time_year_slash_pos);

    LCD::DrawString(Convert2Digit(_time.month()), time_month_pos);
    LCD::DrawString("/", time_month_slash_pos);
    LCD::DrawString(Convert2Digit(_time.day()), time_day_pos);

    LCD::DrawString(Convert2Digit(_time.hour()), time_hour_pos);
    LCD::DrawString(":", time_hour_colon_pos);
    LCD::DrawString(Convert2Digit(_time.minute()), time_minute_pos);
    LCD::DrawString(":", time_minute_colon_pos);
    // 設定を抜けた時点で0秒として打ち込む
    LCD::DrawString("00", time_second_pos);
}

void SettingsState::DrawBrightness()
{
    LCD::FillRect(brightness_bar_pos, brightness_rect, color_black);

    LCD::DrawString("輝度", brightness_title_pos);
    LCD::DrawRect(brightness_bar_pos, brightness_bar_rect, color_white);

    // 輝度をバーで示すために比率を求める
    float width = 240.0 * _brightness->GetValue() / _brightness->max;
    Rect<int32_t> brightness_value_rect(static_cast<int32_t>(width), brightness_bar_rect.Height());

    LCD::FillRect(brightness_bar_pos, brightness_value_rect, color_white);
}

void SettingsState::Up()
{
    if (_mode == SettingsStateMode::Time)
    {
        _mode = SettingsStateMode::Brightness;
    }
    else
    {
        _mode = SettingsStateMode::Time;
    }
    
    DrawModeArrow();
}

void SettingsState::Left()
{
    switch(_mode)
    {
        case SettingsStateMode::Time:
        break;
        case SettingsStateMode::Brightness:
            _brightness->Down();
            DrawBrightness();
        break;
        default:
        break;
    }
}

void SettingsState::Right()
{
    switch(_mode)
    {
        case SettingsStateMode::Time:
        break;
        case SettingsStateMode::Brightness:
            _brightness->Up();
            DrawBrightness();
        break;
        default:
        break;
    }
}

void SettingsState::Start()
{

}

void SettingsState::GameboyA()
{

}

void SettingsState::GameboyB()
{

}

void SettingsState::ButtonA()
{
    // 戻る
    _selector->ToGoodsState();
}

void SettingsState::ButtonC()
{
    // 決定
    _selector->ToGoodsState();
}