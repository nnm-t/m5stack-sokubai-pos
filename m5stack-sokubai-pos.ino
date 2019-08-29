#define ESP32

#include <M5Stack.h>
#include <Ticker.h>
#include <ArduinoJson.h>

#include "sokubai-pos.h"

constexpr Rect<uint32_t> tft_rect(320, 240);

void setup()
{
    M5.begin();
}

void loop()
{
    M5.update();
}