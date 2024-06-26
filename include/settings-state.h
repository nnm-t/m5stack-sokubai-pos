#pragma once

#include "config.h"

#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>

#include "i-state.h"
#include "state-selector.h"
#include "rtc.h"
#include "brightness.h"
#include "settings-state-mode.h"
#include "settings-state-datetime.h"
#include "rfid.h"
#include "esp-now.h"

class SettingsState : public IState
{
    static constexpr Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr int32_t index_x = 40;
    static constexpr Vector2<int32_t> time_title_pos = Vector2<int32_t>(index_x, 60);

    static constexpr Vector2<int32_t> time_triangle0 = Vector2<int32_t>(10, 60);
    static constexpr Vector2<int32_t> time_triangle1 = Vector2<int32_t>(10, 80);
    static constexpr Vector2<int32_t> time_triangle2 = Vector2<int32_t>(30, 70);

    static constexpr Vector2<int32_t> brightness_triangle0 = Vector2<int32_t>(10, 100);
    static constexpr Vector2<int32_t> brightness_triangle1 = Vector2<int32_t>(10, 120);
    static constexpr Vector2<int32_t> brightness_triangle2 = Vector2<int32_t>(30, 110);

    static constexpr int32_t time_y = time_title_pos.Y();
    static constexpr int32_t time_x = 90;
    static constexpr int32_t time_x2 = 230;
    static constexpr int32_t time_w = 12;

    static constexpr Vector2<int32_t> time_bg_pos = Vector2<int32_t>(time_x, 60);
    static constexpr Rect<int32_t> time_bg_rect = Rect<int32_t>(280, 20);

    static constexpr Vector2<int32_t> time_year1000_pos = Vector2<int32_t>(time_x, time_y);
    static constexpr Vector2<int32_t> time_year100_pos = Vector2<int32_t>(time_x + time_w, time_y);
    static constexpr Vector2<int32_t> time_year10_pos = Vector2<int32_t>(time_x + time_w * 2, time_y);
    static constexpr Vector2<int32_t> time_year1_pos = Vector2<int32_t>(time_x + time_w * 3, time_y);

    static constexpr Vector2<int32_t> time_year_slash_pos = Vector2<int32_t>(time_x + time_w * 4, time_y);

    static constexpr Vector2<int32_t> time_month_pos = Vector2<int32_t>(time_x + time_w * 5, time_y);
    static constexpr Vector2<int32_t> time_month_slash_pos = Vector2<int32_t>(time_x + time_w * 7, time_y);
    static constexpr Vector2<int32_t> time_day_pos = Vector2<int32_t>(time_x + time_w * 8, time_y);

    static constexpr Vector2<int32_t> time_hour_pos = Vector2<int32_t>(time_x2, time_y);
    static constexpr Vector2<int32_t> time_hour_colon_pos = Vector2<int32_t>(time_x2 + time_w * 2, time_y);

    static constexpr Vector2<int32_t> time_minute_pos = Vector2<int32_t>(time_x2 + time_w * 3, time_y);

    static constexpr Vector2<int32_t> brightness_title_pos = Vector2<int32_t>(index_x, 100);

    static constexpr Vector2<int32_t> brightness_bar_pos = Vector2<int32_t>(time_x, brightness_title_pos.Y());
    static constexpr Rect<int32_t> brightness_bar_rect = Rect<int32_t>(200, 20);

    static constexpr Rect<int32_t> brightness_rect = Rect<int32_t>(200, 20);

    static constexpr Vector2<int32_t> mac_title_pos = Vector2<int32_t>(40, 125);
    static constexpr Vector2<int32_t> mac_from_title_pos = Vector2<int32_t>(40, 145);
    static constexpr Vector2<int32_t> mac_to_title_pos = Vector2<int32_t>(40, 165);
    static constexpr Vector2<int32_t> mac_from_pos = Vector2<int32_t>(90, 145);
    static constexpr Vector2<int32_t> mac_to_pos = Vector2<int32_t>(90, 165);

    static constexpr Vector2<int32_t> rfid_title_pos = Vector2<int32_t>(40, 190);
    static constexpr Vector2<int32_t> rfid_uuid_pos = Vector2<int32_t>(90, 190);
    static constexpr Rect<int32_t> rfid_rect = Rect<int32_t>(240, 20);

    static constexpr const uint32_t min_interval_ms = 1000;

    StateSelector* const _selector;
    RTC* const _rtc;
    Brightness* const _brightness;
    RFID* const _rfid;
    ESPNOW* const _espnow;
    const uint32_t _delay_ms;

    bool _do_connect = false;
    bool _do_disconnect = false;

    SettingsStateMode _mode = SettingsStateMode::Time;
    SettingsStateDateTime _date_mode = SettingsStateDateTime::Year100;
    DateTime _time = DateTime();
    uint32_t _period_ms = 0;

    void DrawModeArrow();

    void DrawTime();

    void DrawTimeUnderLine();

    void DrawBrightness();

    void DrawMAC();

    void DrawUUID();

    String Convert2Digit(const uint8_t number);

public:
    SettingsState(StateSelector* const selector, RTC* const rtc, Brightness* const brightness, RFID* const rfid, ESPNOW* const espnow, const uint32_t delay_ms) : _selector(selector), _rtc(rtc), _brightness(brightness), _rfid(rfid), _espnow(espnow), _delay_ms(delay_ms)
    {

    }

    FooterText GetFooterText() override;

    void Begin() override;

    void Update() override;

    void Draw() override;

    void Up() override;

    void Down() override;

    void Left() override;

    void Right() override;

    void Start() override;

    void Select() override
    {

    }

    void GameboyA() override;

    void GameboyB() override;

    void GameboyReleased() override
    {

    }

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    void WriteSales() override
    {

    }
};