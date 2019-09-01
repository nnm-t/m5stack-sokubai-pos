#pragma once

#include <Arduino.h>
#include <M5Stack.h>

namespace SokubaiPos
{
    // デフォルト: Rotate90
    enum class Rotation : uint8_t
    {
        Zero = 0, Rotate90 = 1, Rotate180 = 2, Rotate270 = 3,
        Invert = 4, Invert90 = 5, Invert180 = 6, Invert270 = 7
    };
}