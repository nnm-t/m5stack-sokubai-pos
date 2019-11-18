#pragma once

#include "color16.h"
#include "vector2.h"
#include "rect.h"

constexpr char* font_20pt = "mplus-1c20";
constexpr char* font_30pt = "mplus-1c30";
constexpr char* font_40pt = "mplus-1c40";

constexpr Color16 color_white = Color16::From32(0xFFFFFF);
constexpr Color16 color_black = Color16::From32(0x000000);
constexpr Color16 color_red = Color16::From32(0xFF0000);
constexpr Color16 color_yellow = Color16::From32(0xFFFF00);

constexpr const Vector2<int32_t> bg_pos = Vector2<int32_t>(0, 20);
constexpr const Rect<int32_t> bg_rect = Rect<int32_t>(320, 200);

constexpr const Rect<int32_t> title_rect = Rect<int32_t>(200, 20);
constexpr const int32_t title_width = 170;