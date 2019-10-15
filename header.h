#pragma once

#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "vector2.h"
#include "rect.h"
#include "constants.h"

class Header
{
    static constexpr uint8_t font_size = 20;

    static constexpr Vector2<int32_t> battery_pos = Vector2<int32_t>(320, 0);
    static constexpr Vector2<int32_t> wifi_pos = Vector2<int32_t>(0, 0);

public:
    Header()
    {

    }

    void Draw();
};