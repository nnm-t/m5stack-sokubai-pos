#pragma once

#include <memory>
#include <Arduino.h>
#include <M5Stack.h>

#include "i-text.h"
#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "text-datum.h"
#include "lcd-base.h"

namespace SokubaiPos
{
    class Text : public LCDBase, public IText
    {
        uint8_t _size;
        std::shared_ptr<Color16> _foreground;
        std::shared_ptr<Color16> _background;
        TextDatum _datum;

        void SetTextSize();

        void SetTextParameter();

    public:
        Text(TFT_eSPI* tft, const uint8_t size = 8, const Color16& foreground = Color16::White(),
            const Color16& background = Color16::Black(), const TextDatum datum = TextDatum::TopLeft)
        : LCDBase(tft), _size(size), _foreground(std::make_shared<Color16>(foreground)), _background(std::make_shared<Color16>(background)), _datum(datum)
        {

        }

        Text(const uint8_t size = 8, const Color16& foreground = Color16::White(),
            const Color16& background = Color16::Black(), const TextDatum datum = TextDatum::TopLeft)
        : Text(&M5.Lcd, size, foreground, background, datum)
        {

        }

        void Draw(const char* string, const Vector2<int32_t>& position) override;
        
        void Draw(String& string, const Vector2<int32_t>& position) override;

        bool GetFontsLoaded() override;

        uint16_t GetTextWidth(const String& string) override;

        TextDatum GetTextDatum() override;

        void LoadFont(String& font_name, FS& fs = SD) override;

        void LoadFont(const char* font_name, FS& fs = SD) override;

        void Print(const char* string) override;

        void Print(String& string) override;

        void PrintLn(const char* string) override;

        void PrintLn(String& string) override;

        void SetCursor(const Vector2<uint16_t>& position) override;

        void SetSize(const uint8_t size) override;

        void SetForeground(Color16& color) override;

        void SetBackground(const Color16& color) override;

        void UnloadFont() override;
    };
}