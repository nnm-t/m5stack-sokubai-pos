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

class Header
{
    static constexpr const uint32_t interval_ms = 1000;
    static constexpr const uint8_t battery_high = 66;
    static constexpr const uint8_t battery_medium = 33;
    static constexpr const uint8_t battery_low = 0;

    static constexpr Rect<int32_t> background_rect = Rect<int32_t>(240, 20);
    static constexpr Rect<int32_t> battery_rect = Rect<int32_t>(80, 20);

    static constexpr Vector2<int32_t> background_pos = Vector2<int32_t>(0, 0);
    static constexpr Vector2<int32_t> battery_pos = Vector2<int32_t>(320, 0);
    static constexpr Vector2<int32_t> battery_rect_pos = Vector2<int32_t>(240, 0);
    static constexpr Vector2<int32_t> wifi_pos = Vector2<int32_t>(0, 0);

    const uint32_t _delay_ms;

    uint32_t _period_ms = 0;

    void Draw();

    void DrawBatteryLevel(const uint8_t battery_level);

public:
    Header(const uint32_t delay_ms) : _delay_ms(delay_ms)
    {

    }

    void Begin();

    void Update();
};