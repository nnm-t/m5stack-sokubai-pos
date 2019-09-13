#include "diagram.h"

namespace SokubaiPos
{
    void Diagram::DrawCircle(const Vector2<int32_t>& position, const int32_t radius, const Color16& color)
    {
        _tft->drawCircle(position.X(), position.Y(), radius, color.Get());
    }

    void Diagram::DrawRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
    {
        _tft->drawRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
    }

    void Diagram::DrawTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color)
    {
        _tft->drawTriangle(pos0.X(), pos0.Y(), pos1.X(), pos1.Y(), pos2.X(), pos2.Y(), color.Get());
    }

    void Diagram::FillCircle(const Vector2<int32_t>& position, const int32_t radius, const Color16& color)
    {
        _tft->fillCircle(position.X(), position.Y(), radius, color.Get());
    }

    void Diagram::FillRect(const Vector2<int32_t>& position, const Rect<int32_t>& size, const Color16& color)
    {
        _tft->fillRect(position.X(), position.Y(), size.Width(), size.Height(), color.Get());
    }

    void Diagram::FillTriangle(const Vector2<int32_t>& pos0, const Vector2<int32_t>& pos1, const Vector2<int32_t>& pos2, const Color16& color)
    {
        _tft->fillTriangle(pos0.X(), pos0.Y(), pos1.X(), pos1.Y(), pos2.X(), pos2.Y(), color.Get());
    }
}