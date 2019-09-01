#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "../sokubai-pos.h"

namespace SokubaiPos
{
    class Diagram : public LCDBase
    {
    public:
        Diagram(TFT_eSPI* tft) : LCDBase(tft)
        {

        }

        Diagram() : LCDBase()
        {

        }

        void DrawCircle(const Vector2<int32_t>& position, const int32_t radius, const Color16& color = Color16::White())
        {
            _tft->drawCircle(position.X(), position.Y(), radius, color.Get());
        }

        void DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color = Color16::White())
        {
            _tft->drawRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
        }

        void FillCircle(const Vector2<int32_t>& position, const int32_t radius, const Color16& color = Color16::White())
        {
            _tft->fillCircle(position.X(), position.Y(), radius, color.Get());
        }

        void FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color = Color16::White())
        {
            _tft->fillRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
        }
    };
}