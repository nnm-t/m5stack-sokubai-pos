#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "lcd-base.h"

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

        void DrawCircle(const Vector2<int32_t>& position, const int32_t radius, const Color16& color = Color16::White());

        void DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color = Color16::White());

        void DrawTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color);

        void FillCircle(const Vector2<int32_t>& position, const int32_t radius, const Color16& color = Color16::White());

        void FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color = Color16::White());

        void FillTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color);
    };
}