#pragma once

#include <M5Stack.h>

#include "../sokubai-pos.h"
#include "sprite-color-depth.h"

namespace SokubaiPos
{
    class Sprite
    {
        TFT_eSprite _sprite;

        void SetColorDepth(const SpriteColorDepth depth)
        {
            _sprite.setColorDepth(static_cast<uint8_t>(depth));
        }

    public:
        Sprite(TFT_eSPI *tft) : _sprite(TFT_eSprite(tft))
        {

        }

        Sprite() : Sprite(&M5.Lcd)
        {

        }

        void Create(const Rect<uint16_t>& rect, const SpriteColorDepth depth = SpriteColorDepth::Bytes16)
        {
            _sprite.createSprite(rect.Width(), rect.Height());
            SetColorDepth(depth);
        }

        void Delete()
        {
            _sprite.deleteSprite();
        }

        void Fill(const Color16& color)
        {
            _sprite.fillSprite(color.Get());
        }

        TFT_eSprite* Get()
        {
            return &_sprite;
        }

        Rect<uint16_t> GetSize()
        {
            return Rect<uint16_t>(_sprite.width(), _sprite.height());
        }

        void Push(const Vector2<int32_t>& position)
        {
            _sprite.pushSprite(position.X(), position.Y());
        }

        void Push(const Vector2<int32_t>& position, const Color16& transparent)
        {
            _sprite.pushSprite(position.X(), position.Y(), transparent.Get());
        }
    };
}