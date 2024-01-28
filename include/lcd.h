#pragma once

#include "config.h"

#include <Arduino.h>
#include <M5Stack.h>
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "text-datum.h"

class LCD
{
    static LGFX* _lcd;

public:
    static void Init(LGFX* lcd);

    static void SetColorDepth(const uint8_t depth);
    static void FillScreen(const Color16& color);

    static void DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color);

    static void FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color);

    static void SetFont(const lgfx::v1::IFont* font);

    static void DrawString(String string, const Vector2<int32_t>& position);

    static void DrawString(const char* string, const Vector2<int32_t>& position);

    static void SetTextDatum(const TextDatum datum);

    static void DrawTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color);

    static void FillTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color);

    static void DrawCircle(const Vector2<int32_t>& center, const int32_t radius, const Color16& color);

    static void FillCircle(const Vector2<int32_t>& center, const int32_t radius, const Color16& color);

    static void SetTextColor(const Color16& color);

    static void SetTextColor(const Color16& foreground, const Color16& background);

    static void DrawBmpFile(const Vector2<uint16_t>& position, const char* path, fs::FS& fs = SD);

    static void DrawBmpFile(const Vector2<uint16_t>& position, String& path, fs::FS& fs = SD);

    static void DrawLine(const Vector2<int16_t>& pos0, const Vector2<int16_t>& pos1, const Color16& color);

    static void DrawLine(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Color16& color);

    static void SetTextSize(const uint8_t size);
    
    static void SetBrightness(const uint8_t brightness);
};