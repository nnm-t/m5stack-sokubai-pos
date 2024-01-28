#include "lcd.h"

LGFX* LCD::_lcd;

void LCD::Init(LGFX* lcd)
{
  _lcd = lcd;
  _lcd->init();
}

void LCD::SetColorDepth(const uint8_t depth)
{
  _lcd->setColorDepth(depth);
}

void LCD::FillScreen(const Color16& color)
{
    _lcd->fillScreen(color.Get());
}

void LCD::DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    _lcd->drawRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void LCD::FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    _lcd->fillRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void LCD::DrawCircle(const Vector2<int32_t>& center, const int32_t radius, const Color16& color)
{
    _lcd->drawCircle(center.X(), center.Y(), radius, color.Get());
}

void LCD::FillCircle(const Vector2<int32_t>& center, const int32_t radius, const Color16& color)
{
    _lcd->fillCircle(center.X(), center.Y(), radius, color.Get());
}

void LCD::SetFont(const lgfx::v1::IFont* font)
{
    _lcd->setFont(font);
}

void LCD::DrawString(String string, const Vector2<int32_t>& position)
{
    _lcd->drawString(string, position.X(), position.Y());
}

void LCD::DrawString(const char* string, const Vector2<int32_t>& position)
{
    _lcd->drawString(string, position.X(), position.Y());
}

void LCD::SetTextDatum(const TextDatum datum)
{
    _lcd->setTextDatum(static_cast<uint8_t>(datum));
}

void LCD::DrawTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color)
{
    _lcd->drawTriangle(pos0.X(), pos0.Y(), pos1.X(), pos1.Y(), pos2.X(), pos2.Y(), color.Get());
}

void LCD::FillTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color)
{
    _lcd->fillTriangle(pos0.X(), pos0.Y(), pos1.X(), pos1.Y(), pos2.X(), pos2.Y(), color.Get());
}

void LCD::SetTextColor(const Color16& color)
{
    _lcd->setTextColor(color.Get());
}

void LCD::SetTextColor(const Color16& foreground, const Color16& background)
{
    _lcd->setTextColor(foreground.Get(), background.Get());
}

void LCD::DrawBmpFile(const Vector2<uint16_t>& position, const char* path, fs::FS& fs)
{
    _lcd->drawBmpFile(fs, path, position.X(), position.Y());
}

void LCD::DrawBmpFile(const Vector2<uint16_t>& position, String& path, fs::FS& fs)
{
    _lcd->drawBmpFile(fs, path.c_str(), position.X(), position.Y());
}

void LCD::DrawLine(const Vector2<int16_t>& pos0, const Vector2<int16_t>& pos1, const Color16& color)
{
    _lcd->drawLine(pos0.X(), pos0.Y(), pos1.X(), pos1.Y(), color.Get());
}

void LCD::DrawLine(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Color16& color)
{
    _lcd->drawLine(pos0.X(), pos0.Y(), pos1.X(), pos1.Y(), color.Get());
}

void LCD::SetTextSize(const uint8_t size)
{
    _lcd->setTextSize(size);
}

void LCD::SetBrightness(const uint8_t brightness)
{
    _lcd->setBrightness(brightness);
}