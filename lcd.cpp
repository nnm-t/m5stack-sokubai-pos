#include "lcd.h"

namespace SokubaiPos
{
    void LCD::FillScreen(const Color16& color)
    {
        M5.Lcd.fillScreen(color.Get());
    }
    void LCD::GenerateQRCode(const char* string, const Vector2<uint16_t>& position, uint8_t width, const uint8_t version)
    {
        M5.Lcd.qrcode(string, position.X(), position.Y(), width, version);
    }

    void LCD::GenerateQRCode(String& string, const Vector2<uint16_t>& position, const uint8_t width, const uint8_t version)
    {
        M5.Lcd.qrcode(string, position.X(), position.Y(), width, version);
    }

    void LCD::DrawBitmapFile(const char* path, const Vector2<uint16_t>& position, FS& fs)
    {
        M5.Lcd.drawBmpFile(fs, path, position.X(), position.Y());
    }

    void LCD::SetBrightness(uint8_t brightness)
    {
        M5.Lcd.setBrightness(brightness);
    }
}