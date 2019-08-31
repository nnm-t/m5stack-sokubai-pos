#define ESP32

#include <M5Stack.h>
#include <Ticker.h>
#include <ArduinoJson.h>

#include "sokubai-pos.h"

using namespace SokubaiPos;

constexpr Rect<uint32_t> tft_rect(320, 240);
constexpr Rect<uint16_t> sprite_rect(32, 32);

Sprite sprite;

void setup()
{
    M5.begin();

    sprite.Create(sprite_rect);
    sprite.Fill(Color16::White());
}

void loop()
{
    M5.update();
}