#include "text.h"

using namespace std;

namespace SokubaiPos
{
    void Text::SetTextSize()
    {
        _tft->setTextSize(_size);
    }

    void Text::SetTextParameter()
    {
        SetTextSize();
        _tft->setTextDatum(static_cast<uint8_t>(_datum));
        _tft->setTextColor(_foreground->Get(), _background->Get());
    }

    void Text::Draw(const char* string, const Vector2<int32_t>& position)
    {
        SetTextParameter();
        _tft->drawString(string, position.X(), position.Y());
    }

    void Text::Draw(String& string, const Vector2<int32_t>& position)
    {
        SetTextParameter();
        _tft->drawString(string, position.X(), position.Y());
    }

    bool Text::GetFontsLoaded()
    {
        return _tft->fontsLoaded();
    }

    uint16_t Text::GetTextWidth(const String& string)
    {
        SetTextSize();
        return _tft->textWidth(string);
    }

    TextDatum Text::GetTextDatum()
    {
        return static_cast<TextDatum>(_tft->getTextDatum());
    }

    void Text::LoadFont(String& font_name, FS& fs)
    {
        _tft->loadFont(font_name, fs);
    }

    void Text::LoadFont(const char* font_name, FS& fs)
    {
        _tft->loadFont(font_name, fs);
    }

    void Text::Print(const char* string)
    {
        SetTextParameter();
        _tft->print(string);
    }

    void Text::Print(String& string)
    {
        SetTextParameter();
        _tft->println(string);
    }

    void Text::PrintLn(const char* string)
    {
        SetTextParameter();
        _tft->println(string);
    }

    void Text::PrintLn(String& string)
    {
        SetTextParameter();
        _tft->println(string);
    }

    void Text::SetCursor(const Vector2<uint16_t>& position)
    {
        _tft->setCursor(position.X(), position.Y());
    }

    void Text::SetSize(const uint8_t size)
    {
        _size = size;
    }

    void Text::SetForeground(Color16& color)
    {
        _foreground = make_shared<Color16>(color);
    }

    void Text::SetBackground(const Color16& color)
    {
        _background = make_shared<Color16>(color);
    }

    void Text::UnloadFont()
    {
        _tft->unloadFont();
    }
}