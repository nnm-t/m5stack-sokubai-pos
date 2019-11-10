#pragma once

#include <Arduino.h>
#include <M5Stack.h>

enum class SpriteColorDepth : uint8_t
{
    Depth16 = 16,
    Depth8 = 8,
    Depth1 = 1
};