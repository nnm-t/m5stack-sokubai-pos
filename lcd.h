#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "text-datum.h"

class LCD
{
public:
    static void DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color);

    static void FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color);

    static void LoadFont(String& fontName, fs::FS& ffs = SD);

    static void LoadFont(const char* fontName, fs::FS& ffs = SD);

    static void DrawString(String string, const Vector2<int32_t>& position);

    static void DrawString(const char* string, const Vector2<int32_t>& position);

    static void SetTextDatum(const TextDatum datum);
};