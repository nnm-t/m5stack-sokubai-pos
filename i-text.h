#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "color16.h"
#include "text-datum.h"

namespace SokubaiPos
{
    class IText
    {
        virtual void Draw(const char* string, const Vector2<int32_t>& position) = 0;
        
        virtual void Draw(String& string, const Vector2<int32_t>& position) = 0;

        virtual bool GetFontsLoaded() = 0;

        virtual uint16_t GetTextWidth(const String& string) = 0;

        virtual TextDatum GetTextDatum() = 0;

        virtual void LoadFont(String& font_name, FS& fs = SD) = 0;

        virtual void LoadFont(const char* font_name, FS& fs = SD) = 0;

        virtual void Print(const char* string) = 0;

        virtual void Print(String& string) = 0;

        virtual void PrintLn(const char* string) = 0;

        virtual void PrintLn(String& string) = 0;

        virtual void SetCursor(const Vector2<uint16_t>& position) = 0;

        virtual void SetSize(const uint8_t size) = 0;

        virtual void SetForeground(Color16& color) = 0;

        virtual void SetBackground(const Color16& color) = 0;

        virtual void UnloadFont() = 0;
    };
}