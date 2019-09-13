#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "color16.h"
#include "vector2.h"

namespace SokubaiPos
{
    class LCD
    {
    public:
        static void FillScreen(const Color16& color);

        static void GenerateQRCode(const char* string, const Vector2<uint16_t>& position, uint8_t width, const uint8_t version = 6);

        static void GenerateQRCode(String& string, const Vector2<uint16_t>& position, const uint8_t width, const uint8_t version = 6);

        static void DrawBitmapFile(const char* path, const Vector2<uint16_t>& position, FS& fs = SD);

        static void SetBrightness(uint8_t brightness);
    };
}