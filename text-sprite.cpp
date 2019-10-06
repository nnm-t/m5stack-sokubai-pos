#include "text-sprite.h"

namespace SokubaiPos
{
    void TextSprite::Draw(const char* string, const Vector2<int32_t>& position)
    {
        _text.Draw(string, position);
    }

    void TextSprite::Draw(String& string, const Vector2<int32_t>& position)
    {
        _text.Draw(string, position);
    }

    bool TextSprite::GetFontsLoaded()
    {
        return _text.GetFontsLoaded();
    }

    uint16_t TextSprite::GetTextWidth(const String& string)
    {
        return _text.GetTextWidth(string);
    }

    void TextSprite::LoadFont(String& font_name, FS& fs)
    {
        _text.LoadFont(font_name, fs);
    }

    void TextSprite::LoadFont(const char* font_name, FS& fs)
    {
        _text.LoadFont(font_name, fs);
    }

    void TextSprite::Print(const char* string)
    {
        _text.Print(string);
    }

    void TextSprite::Print(String& string)
    {
        _text.Print(string);
    }

    void TextSprite::PrintLn(const char* string)
    {
        _text.PrintLn(string);
    }

    void TextSprite::PrintLn(String& string)
    {
        _text.PrintLn(string);
    }

    void TextSprite::SetCursor(const Vector2<uint16_t>& position)
    {
        _text.SetCursor(position);
    }

    void TextSprite::SetSize(const uint8_t size)
    {
        _text.SetSize(size);
    }

    void TextSprite::SetForeground(Color16& color)
    {
        _text.SetForeground(color);
    }

    void TextSprite::SetBackground(const Color16& color)
    {
        _text.SetBackground(color);
    }

    void TextSprite::UnloadFont()
    {
        _text.UnloadFont();
    }
}