#pragma once

#include <Arduino.h>
#include <M5Stack.h>
#include <M5Display.h>

#include "color16.h"
#include "rect.h"
#include "vector2.h"
#include "sprite-color-depth.h"

namespace SokubaiPos
{
    class Sprite
    {
        TFT_eSprite _sprite;

        void SetColorDepth(const SpriteColorDepth depth);

    public:
        Sprite(TFT_eSPI *tft) : _sprite(TFT_eSprite(tft))
        {

        }

        Sprite() : Sprite(&M5.Lcd)
        {

        }

        void Create(const Rect<uint16_t>& rect, const SpriteColorDepth depth = SpriteColorDepth::Bytes16);

        void Delete();

        void Fill(const Color16& color);

        inline TFT_eSprite* Get();

        Rect<uint16_t> GetSize();

        void Push(const Vector2<int32_t>& position);

        void Push(const Vector2<int32_t>& position, const Color16& transparent);
    };
}