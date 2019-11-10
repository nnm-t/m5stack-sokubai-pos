#include "sprite.h"

void* Sprite::Create(const Rect<int16_t>& size, const SpriteColorDepth color_depth, const uint8_t frames)
{
    _sprite.setColorDepth(static_cast<uint8_t>(color_depth));
    return _sprite.createSprite(size.Width(), size.Height(), frames);
}

void Sprite::Fill(const Color16& color)
{
    _sprite.fillSprite(color.Get());
}

void Sprite::SetTextColor(const Color16& color)
{
    _sprite.setTextColor(color.Get());
}

void Sprite::SetTextColor(const Color16& foreground, const Color16& background)
{
    _sprite.setTextColor(foreground.Get(), background.Get());
}

void Sprite::SetTextDatum(const TextDatum datum)
{
    _sprite.setTextDatum(static_cast<uint8_t>(datum));
}

void Sprite::SetScrollRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    _sprite.setScrollRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void Sprite::Scroll(const Vector2<int16_t>& position)
{
    _sprite.scroll(position.X(), position.Y());
}

void Sprite::DrawString(const char* string, const Vector2<int32_t>& position)
{
    _sprite.drawString(string, position.X(), position.Y());
}

void Sprite::DrawString(const String& string, const Vector2<int32_t>& position)
{
    _sprite.drawString(string, position.X(), position.Y());
}

void Sprite::DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    _sprite.drawRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void Sprite::FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    _sprite.fillRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void Sprite::LoadFont(const String& font_name, fs::FS& ffs)
{
    _sprite.loadFont(font_name, ffs);
}

void Sprite::LoadFont(const char* font_name, fs::FS& ffs)
{
    _sprite.loadFont(font_name, ffs);
}

void Sprite::Push(const Vector2<int32_t>& position)
{
    _sprite.pushSprite(position.X(), position.Y());
}

void Sprite::Push(const Vector2<int32_t>& position, const Color16& transparent)
{
    _sprite.pushSprite(position.X(), position.Y(), transparent.Get());
}

void Sprite::Delete()
{
    _sprite.deleteSprite();
}