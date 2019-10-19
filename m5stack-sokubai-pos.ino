#define ESP32

#include <M5Stack.h>
#include <ArduinoJson.h>

#include "constants.h"
#include "vector2.h"
#include "rect.h"
#include "color16.h"
#include "header.h"
#include "footer.h"
#include "goods-list.h"

constexpr const char* json_name = "/goods.json";

Header header;
Footer footer;
GoodsList goods_list;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    SD.begin();

    M5.Lcd.fillScreen(0xFFFF);

    header.Draw();
    footer.Draw();
    goods_list.Begin(json_name);
}

void loop()
{
    M5.update();
}