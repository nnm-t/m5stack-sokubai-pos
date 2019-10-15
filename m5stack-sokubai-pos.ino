#define ESP32

#include <M5Stack.h>
#include <ArduinoJson.h>

#include "constants.h"
#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "header.h"

Header header;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    SD.begin();

    M5.Lcd.fillScreen(0xFFFF);

    header.Draw();
}

void loop()
{
    M5.update();
}