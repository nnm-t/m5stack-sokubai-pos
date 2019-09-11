#include "sprite.h"

namespace SokubaiPos
{
    void Sprite::SetColorDepth(const SpriteColorDepth depth)
    {
        _sprite.setColorDepth(static_cast<uint8_t>(depth));
    }

    void Sprite::Create(const Rect<uint16_t>& rect, const SpriteColorDepth depth)
    {
        _sprite.createSprite(rect.Width(), rect.Height());
        SetColorDepth(depth);
    }

    void Sprite::Delete()
    {
        _sprite.deleteSprite();
    }

    void Sprite::Fill(const Color16& color)
    {
        _sprite.fillSprite(color.Get());
    }

    TFT_eSprite* Get()
    {
        return &_sprite;
    }

    Rect<uint16_t> Sprite::GetSize()
    {
        return Rect<uint16_t>(_sprite.width(), _sprite.height());
    }

    void Sprite::Push(const Vector2<int32_t>& position)
    {
        _sprite.pushSprite(position.X(), position.Y());
    }

    void Sprite::Push(const Vector2<int32_t>& position, const Color16& transparent)
    {
        _sprite.pushSprite(position.X(), position.Y(), transparent.Get());
    }
}