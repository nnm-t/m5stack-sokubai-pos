#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "state-selector.h"
#include "rtc.h"
#include "brightness.h"
#include "settings-state-mode.h"

class SettingsState : public IState
{
    static constexpr Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr int32_t index_x = 40;
    static constexpr Vector2<int32_t> time_title_pos = Vector2<int32_t>(index_x, 60);

    static constexpr Vector2<int32_t> time_triangle0 = Vector2<int32_t>(10, 60);
    static constexpr Vector2<int32_t> time_triangle1 = Vector2<int32_t>(10, 80);
    static constexpr Vector2<int32_t> time_triangle2 = Vector2<int32_t>(30, 70);

    static constexpr Vector2<int32_t> brightness_triangle0 = Vector2<int32_t>(10,120);
    static constexpr Vector2<int32_t> brightness_triangle1 = Vector2<int32_t>(10,140);
    static constexpr Vector2<int32_t> brightness_triangle2 = Vector2<int32_t>(30,130);

    static constexpr int32_t time_y = 90;
    static constexpr int32_t time_x = 20;
    static constexpr int32_t time_x2 = 180;
    static constexpr int32_t time_w = 15;

    static constexpr Vector2<int32_t> time_bg_pos = Vector2<int32_t>(time_x, 60);
    static constexpr Rect<int32_t> time_bg_rect = Rect<int32_t>(280, 55);

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
    static constexpr Vector2<int32_t> time_minute_colon_pos = Vector2<int32_t>(time_x2 + time_w * 5, time_y);

    static constexpr Vector2<int32_t> time_second_pos = Vector2<int32_t>(time_x2 + time_w * 6, time_y);

    static constexpr Vector2<int32_t> brightness_title_pos = Vector2<int32_t>(index_x, 120);

    static constexpr Vector2<int32_t> brightness_bar_pos = Vector2<int32_t>(index_x, 150);
    static constexpr Rect<int32_t> brightness_bar_rect = Rect<int32_t>(240, 20);

    static constexpr Rect<int32_t> brightness_rect = Rect<int32_t>(240, 50);

    StateSelector* const _selector;
    RTC* const _rtc;
    Brightness* const _brightness;

    SettingsStateMode _mode = SettingsStateMode::Time;
    DateTime _time = DateTime();

    void DrawModeArrow();

    void DrawTime();

    void DrawBrightness();

    String Convert2Digit(const uint8_t number);

public:
    SettingsState(StateSelector* const selector, RTC* const rtc, Brightness* const brightness) : _selector(selector), _rtc(rtc), _brightness(brightness)
    {

    }

    FooterText GetFooterText() override;

    void Begin() override;

    void Update() override
    {

    }

    void Draw() override;

    void Up() override;

    void Down() override
    {
        Up();
    }

    void Left() override;

    void Right() override;

    void Start() override;

    void Select() override
    {

    }

    void GameboyA() override;

    void GameboyB() override;

    void ButtonA() override;

    void ButtonB() override
    {

    }

    void ButtonC() override;

    void WriteSales() override
    {

    }
};