#include "settings-state.h"

constexpr Vector2<int32_t> SettingsState::title_pos;
constexpr Vector2<int32_t> SettingsState::time_title_pos;
constexpr Vector2<int32_t> SettingsState::time_triangle0;
constexpr Vector2<int32_t> SettingsState::time_triangle1;
constexpr Vector2<int32_t> SettingsState::time_triangle2;
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

    DateTime now = _rtc->GetNow();

    LCD::SetTextColor(color_white, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);

    LCD::DrawString("設定", title_pos);

    LCD::DrawString("時刻", time_title_pos);
    LCD::FillTriangle(time_triangle0, time_triangle1, time_triangle2, color_red);

    const uint16_t year = now.year();
    LCD::DrawString(String(year / 1000, DEC), time_year1000_pos);
    LCD::DrawString(String(year % 1000, DEC), time_year100_pos);
    LCD::DrawString(String(year % 100, DEC), time_year10_pos);
    LCD::DrawString(String(year % 10, DEC), time_year1_pos);
    LCD::DrawString("/", time_year_slash_pos);

    LCD::DrawString(String(now.month(), DEC), time_month_pos);
    LCD::DrawString("/", time_month_slash_pos);
    LCD::DrawString(String(now.day(), DEC), time_day_pos);

    LCD::DrawString(String(now.hour(), DEC), time_hour_pos);
    LCD::DrawString(":", time_hour_colon_pos);
    LCD::DrawString(String(now.minute(), DEC), time_minute_pos);
    LCD::DrawString(":", time_minute_colon_pos);
    // 設定を抜けた時点で0秒として打ち込む
    LCD::DrawString("00", time_second_pos);

    LCD::DrawString("輝度", brightness_title_pos);
    LCD::DrawRect(brightness_bar_pos, brightness_bar_rect, color_white);
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