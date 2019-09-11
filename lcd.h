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
        static void FillScreen(const Color16& color)
        {
            M5.Lcd.fillScreen(color.Get());
        }

        static void GenerateQRCode(const char* string, const Vector2<uint16_t>& position, uint8_t width, const uint8_t version = 6)
        {
            M5.Lcd.qrcode(string, position.X(), position.Y(), width, version);
        }

        static void GenerateQRCode(String& string, const Vector2<uint16_t>& position, const uint8_t width, const uint8_t version = 6)
        {
            M5.Lcd.qrcode(string, position.X(), position.Y(), width, version);
        }

        static void DrawBitmapFile(const char* path, const Vector2<uint16_t>& position, FS& fs = SD)
        {
            M5.Lcd.drawBmpFile(fs, path, position.X(), position.Y());
        }

        static void SetBrightness(uint8_t brightness)
        {
            M5.Lcd.setBrightness(brightness);
        }
    };
}