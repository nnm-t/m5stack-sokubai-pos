#pragma once

#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "vector2.h"
#include "rect.h"
#include "constants.h"
#include "text-datum.h"
#include "lcd.h"
#include "power.h"
#include "rtc.h"

class Header
{
    static constexpr const uint32_t interval_ms = 500;

    static constexpr const int32_t circle_radius = 8;

    static constexpr const uint8_t battery_high = 66;
    static constexpr const uint8_t battery_medium = 33;
    static constexpr const uint8_t battery_low = 0;

    static constexpr Rect<int32_t> background_rect = Rect<int32_t>(240, 20);
    static constexpr Rect<int32_t> battery_rect = Rect<int32_t>(80, 20);

    static constexpr Vector2<int32_t> background_pos = Vector2<int32_t>(0, 0);

    static constexpr Vector2<int32_t> hour_pos = Vector2<int32_t>(10, 0);
    static constexpr Vector2<int32_t> hour_slash_pos = Vector2<int32_t>(40, 0);
    static constexpr Vector2<int32_t> minute_pos = Vector2<int32_t>(55, 0);
    static constexpr Vector2<int32_t> minute_slash_pos = Vector2<int32_t>(85, 0);
    static constexpr Vector2<int32_t> second_pos = Vector2<int32_t>(100, 0);

    static constexpr Vector2<int32_t> battery_pos = Vector2<int32_t>(320, 1);
    static constexpr Vector2<int32_t> battery_rect_pos = Vector2<int32_t>(240, 0);
    static constexpr Vector2<int32_t> connected_pos = Vector2<int32_t>(20, 1);

    RTC* const _rtc;
    const uint32_t _delay_ms;

    uint32_t _period_ms = 0;
    int8_t _battery_level = -1;
    bool _is_ready = false;

    void Draw();

    void DrawTime();

    void DrawBatteryLevel(const int8_t battery_level);

    String Convert2Digit(const uint8_t value);

public:
    Header(RTC* const rtc, const uint32_t delay_ms) : _rtc(rtc), _delay_ms(delay_ms)
    {

    }

    void Begin();

    void Update();
};