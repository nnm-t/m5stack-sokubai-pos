#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "vector2.h"
#include "rect.h"
#include "constants.h"
#include "lcd.h"

class Footer
{
    static constexpr Rect<int32_t> background_rect = Rect<int32_t>(320, 21);
    static constexpr Rect<int32_t> border_rect = Rect<int32_t>(80, 20);

    static constexpr Vector2<int32_t> background_pos = Vector2<int32_t>(0, 219);
    static constexpr Vector2<int32_t> left_pos = Vector2<int32_t>(20, 220);
    static constexpr Vector2<int32_t> center_pos = Vector2<int32_t>(120, 220);
    static constexpr Vector2<int32_t> right_pos = Vector2<int32_t>(220, 220);

    static constexpr Vector2<int32_t> left_text_pos = Vector2<int32_t>(60, 221);
    static constexpr Vector2<int32_t> right_text_pos = Vector2<int32_t>(260, 221);

public:
    Footer()
    {

    }

    void Draw();
};