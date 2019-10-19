#include "lcd.h"

void LCD::DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    M5.Lcd.drawRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void LCD::FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
{
    M5.Lcd.fillRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
}

void LCD::LoadFont(String& fontName, fs::FS& ffs)
{
    M5.Lcd.loadFont(fontName, ffs);
}

void LCD::LoadFont(const char* fontName, fs::FS& ffs)
{
    M5.Lcd.loadFont(fontName, ffs);
}

void LCD::DrawString(String string, const Vector2<int32_t>& position)
{
    M5.Lcd.drawString(string, position.X(), position.Y());
}

void LCD::DrawString(const char* string, const Vector2<int32_t>& position)
{
    M5.Lcd.drawString(string, position.X(), position.Y());
}

void LCD::SetTextDatum(const TextDatum datum)
{
    M5.Lcd.setTextDatum(static_cast<uint8_t>(datum));
}