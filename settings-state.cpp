#include "settings-state.h"

constexpr Vector2<int32_t> SettingsState::title_pos;
constexpr Vector2<int32_t> SettingsState::time_title_pos;
constexpr Vector2<int32_t> SettingsState::time_triangle0;
constexpr Vector2<int32_t> SettingsState::time_triangle1;
constexpr Vector2<int32_t> SettingsState::time_triangle2;
constexpr Vector2<int32_t> SettingsState::brightness_triangle0;
constexpr Vector2<int32_t> SettingsState::brightness_triangle1;
constexpr Vector2<int32_t> SettingsState::brightness_triangle2;
constexpr Vector2<int32_t> SettingsState::ble_triangle0;
constexpr Vector2<int32_t> SettingsState::ble_triangle1;
constexpr Vector2<int32_t> SettingsState::ble_triangle2;
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
constexpr Vector2<int32_t> SettingsState::brightness_title_pos;
constexpr Vector2<int32_t> SettingsState::brightness_bar_pos;
constexpr Rect<int32_t> SettingsState::brightness_bar_rect;
constexpr Rect<int32_t> SettingsState::brightness_rect;

FooterText SettingsState::GetFooterText()
{
    return FooterText("戻る", "BLE接続", "決定");
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

    DrawTime();
    DrawBrightness();
    DrawBLE();

    DrawModeArrow();
    DrawTimeUnderLine();
}

void SettingsState::DrawModeArrow()
{
    LCD::FillTriangle(time_triangle0, time_triangle1, time_triangle2, color_black);
    LCD::FillTriangle(brightness_triangle0, brightness_triangle1, brightness_triangle2, color_black);
            LCD::FillTriangle(ble_triangle0, ble_triangle1, ble_triangle2, color_black);

    switch(_mode)
    {
        case SettingsStateMode::Time:
            // 時刻
            LCD::FillTriangle(time_triangle0, time_triangle1, time_triangle2, color_red);
            break;
        case SettingsStateMode::Brightness:
            // 輝度
            LCD::FillTriangle(brightness_triangle0, brightness_triangle1, brightness_triangle2, color_red);
            break;
        case SettingsStateMode::BLE:
            LCD::FillTriangle(ble_triangle0, ble_triangle1, ble_triangle2, color_red);
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
    LCD::FillRect(time_year1000_pos, time_bg_rect, color_black);

    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("時刻", time_title_pos);

    const uint16_t year = _time.year();
    LCD::DrawString(String(year / 1000, DEC), time_year1000_pos);
    LCD::DrawString(String((year % 1000) / 100, DEC), time_year100_pos);
    LCD::DrawString(String((year % 100) / 10, DEC), time_year10_pos);
    LCD::DrawString(String(year % 10, DEC), time_year1_pos);
    LCD::DrawString("/", time_year_slash_pos);

    LCD::DrawString(Convert2Digit(_time.month()), time_month_pos);
    LCD::DrawString("/", time_month_slash_pos);
    LCD::DrawString(Convert2Digit(_time.day()), time_day_pos);

    LCD::DrawString(Convert2Digit(_time.hour()), time_hour_pos);
    LCD::DrawString(":", time_hour_colon_pos);
    LCD::DrawString(Convert2Digit(_time.minute()), time_minute_pos);
}

void SettingsState::DrawTimeUnderLine()
{
    constexpr Rect<int32_t> digit1_rect = Rect<int32_t>(time_w, 2);
    constexpr Rect<int32_t> digit2_rect = Rect<int32_t>(time_w * 2, 2);
    constexpr int32_t digit_pos_y = time_y + 20;

    LCD::FillRect(Vector2<int32_t>(time_year1000_pos.X(), digit_pos_y), Rect<int32_t>(280, 2), color_black);

    // 下線
    switch (_date_mode)
    {
    case SettingsStateDateTime::Year100:
        LCD::FillRect(Vector2<int32_t>(time_year100_pos.X(), digit_pos_y), digit1_rect, color_red);
        break;
    case SettingsStateDateTime::Year10:
        LCD::FillRect(Vector2<int32_t>(time_year10_pos.X(), digit_pos_y), digit1_rect, color_red);
        break;
    case SettingsStateDateTime::Year1:
        LCD::FillRect(Vector2<int32_t>(time_year1_pos.X(), digit_pos_y), digit1_rect, color_red);
        break;
    case SettingsStateDateTime::Month:
        LCD::FillRect(Vector2<int32_t>(time_month_pos.X(), digit_pos_y), digit2_rect, color_red);
        break;
    case SettingsStateDateTime::Day:
        LCD::FillRect(Vector2<int32_t>(time_day_pos.X(), digit_pos_y), digit2_rect, color_red);
        break;
    case SettingsStateDateTime::Hour:
        LCD::FillRect(Vector2<int32_t>(time_hour_pos.X(), digit_pos_y), digit2_rect, color_red);
        break;
    case SettingsStateDateTime::Minute:
        LCD::FillRect(Vector2<int32_t>(time_minute_pos.X(), digit_pos_y), digit2_rect, color_red);
        break;
    default:
        break;
    }
}

void SettingsState::DrawBrightness()
{
    LCD::FillRect(brightness_bar_pos, brightness_rect, color_black);

    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("輝度", brightness_title_pos);
    LCD::DrawRect(brightness_bar_pos, brightness_bar_rect, color_white);

    // 輝度をバーで示すために比率を求める
    float width = 200.0 * _brightness->GetValue() / _brightness->max;
    Rect<int32_t> brightness_value_rect(static_cast<int32_t>(width), brightness_bar_rect.Height());

    LCD::FillRect(brightness_bar_pos, brightness_value_rect, color_white);
}

void SettingsState::DrawBLE()
{
    LCD::FillRect(Vector2<int32_t>(40, 140), Rect<int32_t>(240, 20), color_black);

    LCD::SetTextColor(color_white, color_black);
    LCD::DrawString("BLE", Vector2<int32_t>(40, 140));

    LCD::DrawString("Scan", Vector2<int32_t>(90, 140));

    // todo: MACアドレス書き出されない
    if (_ble->IsAdvertised())
    {
        LCD::DrawString(_ble->GetAdvertisedDeviceAddress(), Vector2<int32_t>(160, 140));
    }
}

void SettingsState::Up()
{
    switch (_mode)
    {
        case SettingsStateMode::Time:
            _mode = SettingsStateMode::BLE;
            break;
        case SettingsStateMode::Brightness:
            _mode = SettingsStateMode::Time;
            break;
        case SettingsStateMode::BLE:
            _mode = SettingsStateMode::Brightness;
            break;
    }
    
    DrawModeArrow();
}

void SettingsState::Down()
{
    switch (_mode)
    {
        case SettingsStateMode::Time:
            _mode = SettingsStateMode::Brightness;
            break;
        case SettingsStateMode::Brightness:
            _mode = SettingsStateMode::BLE;
            break;
        case SettingsStateMode::BLE:
            _mode = SettingsStateMode::Time;
            break;
    }
    
    DrawModeArrow();
}

void SettingsState::Left()
{
    switch(_mode)
    {
        case SettingsStateMode::Time:
            if (_date_mode == SettingsStateDateTime::Year100)
            {
                _date_mode = SettingsStateDateTime::Minute;
            }
            else
            {
                _date_mode = static_cast<SettingsStateDateTime>(static_cast<uint8_t>(_date_mode) - 1);
            }

            DrawTimeUnderLine();
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
            if (_date_mode == SettingsStateDateTime::Minute)
            {
                _date_mode = SettingsStateDateTime::Year100;
            }
            else
            {
                _date_mode = static_cast<SettingsStateDateTime>(static_cast<uint8_t>(_date_mode) + 1);
            }

            DrawTimeUnderLine();
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
    if (_mode == SettingsStateMode::BLE)
    {
        _ble->Scan();
    }
    else if (_mode != SettingsStateMode::Time)
    {
        return;
    }

    // インクリメント
    uint16_t year = _time.year();
    uint8_t month = _time.month();
    uint8_t day = _time.day();
    uint8_t hour = _time.hour();
    uint8_t minute = _time.minute();
    switch (_date_mode)
    {
    case SettingsStateDateTime::Year100:
        if (year > 2899)
        {
            break;
        }

        year += 100;
        break;
    case SettingsStateDateTime::Year10:
        if (year > 2989)
        {
            break;
        }

        year += 10;
        break;
    case SettingsStateDateTime::Year1:
        if (year > 2998)
        {
            break;
        }

        year++;
        break;
    case SettingsStateDateTime::Month:
        if (month >= 12)
        {
            month = 1;
        }
        else
        {
            month++;
        }
        break;
    case SettingsStateDateTime::Day:
        switch(month)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day >= 31)
                {
                    day = 1;
                }
                else
                {
                    day++;
                }
            break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day >= 30)
                {
                    day = 1;
                }
                else
                {
                    day++;
                }
            break;
            case 2:
                // 2100年対応は省略
                if (day >= 29 && year % 4 == 0)
                {
                    day = 1;
                }
                else if (day >= 28 && year % 4 != 0)
                {
                    day = 1;
                }
                else
                {
                    day++;
                }
            break;
        }
        break;
    case SettingsStateDateTime::Hour:
        if (hour >= 23)
        {
            hour = 0;
        }
        else
        {
            hour++;
        }
        break;
    case SettingsStateDateTime::Minute:
        if (minute >= 59)
        {
            minute = 0;
        }
        else
        {
            minute++;
        }
        break;
    default:
        break;
    }

    _time = DateTime(year, month, day, hour, minute, 0);

    DrawTime();
    DrawModeArrow();
}

void SettingsState::GameboyB()
{
    if (_mode != SettingsStateMode::Time)
    {
        return;
    }

    // デクリメント
    uint16_t year = _time.year();
    uint8_t month = _time.month();
    uint8_t day = _time.day();
    uint8_t hour = _time.hour();
    uint8_t minute = _time.minute();
    switch (_date_mode)
    {
    case SettingsStateDateTime::Year100:
        if (year <= 1000)
        {
            break;
        }

        year -= 100;
        break;
    case SettingsStateDateTime::Year10:
        if (year <= 100)
        {
            break;
        }

        year -= 10;
        break;
    case SettingsStateDateTime::Year1:
        if (year <= 1)
        {
            break;
        }

        year--;
        break;
    case SettingsStateDateTime::Month:
        if (month <= 1)
        {
            month = 12;
        }
        else
        {
            month--;
        }
        break;
    case SettingsStateDateTime::Day:
        switch(month)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if (day <= 1)
                {
                    day = 31;
                }
                else
                {
                    day--;
                }
            break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (day <= 1)
                {
                    day = 30;
                }
                else
                {
                    day--;
                }
            break;
            case 2:
                // 2100年対応は省略
                if (day <= 1 && year % 4 == 0)
                {
                    day = 29;
                }
                else if (day <= 1 && year % 4 != 0)
                {
                    day = 28;
                }
                else
                {
                    day--;
                }
            break;
        }
        break;
    case SettingsStateDateTime::Hour:
        if (hour == 0)
        {
            hour = 23;
        }
        else
        {
            hour--;
        }
        break;
    case SettingsStateDateTime::Minute:
        if (minute == 00)
        {
            minute = 59;
        }
        else
        {
            minute--;
        }
        break;
    default:
        break;
    }

    _time = DateTime(year, month, day, hour, minute, 0);

    DrawTime();
    DrawModeArrow();
}

void SettingsState::ButtonA()
{
    // 戻る
    _selector->ToGoodsState();
}

void SettingsState::ButtonC()
{
    // 決定
    _rtc->Adjust(_time);
    _selector->ToGoodsState();
}

void SettingsState::Update()
{
    _period_ms += _delay_ms;

    if (_period_ms >= min_interval_ms)
    {
        _period_ms = 0;
        DrawBLE();
    }
}