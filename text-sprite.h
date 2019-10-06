#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-text.h"
#include "sprite.h"
#include "text.h"
#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "text-datum.h"

namespace SokubaiPos
{
    class TextSprite : public Sprite, public IText
    {
        Text _text;

    public:
        TextSprite(TFT_eSPI *tft, const uint8_t size = 8, const Color16& foreground = Color16::White(),
            const Color16& background = Color16::Black(), const TextDatum datum = TextDatum::TopLeft)
        : Sprite(tft), _text(Text(&_sprite, size, foreground, background, datum))
        {

        }

        TextSprite(const uint8_t size, const Color16& foreground = Color16::White(),
            const Color16& background = Color16::Black(), const TextDatum datum = TextDatum::TopLeft)
        : Sprite(), _text(Text(&_sprite, size, background, foreground, datum))
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