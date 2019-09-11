#pragma once

#include <memory>
#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "text-datum.h"
#include "lcd-base.h"

namespace SokubaiPos
{
    class Text : public LCDBase
    {
        uint8_t _size;
        std::shared_ptr<Color16> _foreground;
        std::shared_ptr<Color16> _background;
        TextDatum _datum;

        void SetTextSize()
        {
            _tft->setTextSize(_size);
        }

        void SetTextParameter()
        {
            SetTextSize();
            _tft->setTextDatum(static_cast<uint8_t>(_datum));
            _tft->setTextColor(_foreground->Get(), _background->Get());
        }

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

        void Draw(const char* string, const Vector2<int32_t>& position)
        {
            SetTextParameter();
            _tft->drawString(string, position.X(), position.Y());
        }

        void Draw(String& string, const Vector2<int32_t>& position)
        {
            SetTextParameter();
            _tft->drawString(string, position.X(), position.Y());
        }

        bool GetFontsLoaded()
        {
            return _tft->fontsLoaded();
        }

        uint16_t GetTextWidth(const String& string)
        {
            SetTextSize();
            return _tft->textWidth(string);
        }

        TextDatum GetTextDatum()
        {
            return static_cast<TextDatum>(_tft->getTextDatum());
        }

        void LoadFont(String& font_name, FS& fs = SD)
        {
            _tft->loadFont(font_name, fs);
        }

        void LoadFont(const char* font_name, FS& fs = SD)
        {
            _tft->loadFont(font_name, fs);
        }

        void Print(const char* string)
        {
            SetTextParameter();
            _tft->print(string);
        }

        void Print(String& string)
        {
            SetTextParameter();
            _tft->println(string);
        }

        void PrintLn(const char* string)
        {
            SetTextParameter();
            _tft->println(string);
        }

        void PrintLn(String& string)
        {
            SetTextParameter();
            _tft->println(string);
        }

        void SetCursor(const Vector2<uint16_t>& position)
        {
            _tft->setCursor(position.X(), position.Y());
        }

        void SetSize(const uint8_t size)
        {
            _size = size;
        }

        void SetForeground(Color16& color)
        {
            _foreground = std::make_shared<Color16>(color);
        }

        void SetBackground(const Color16& color)
        {
            _background = std::make_shared<Color16>(color);
        }

        void UnloadFont()
        {
            _tft->unloadFont();
        }
    };
}