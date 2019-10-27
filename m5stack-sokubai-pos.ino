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
#include "goods-state.h"
#include "keyboard.h"

constexpr const char* json_filename = "/goods.json";

Header header;
Footer footer;
GoodsList goods_list(json_filename);
GoodsState goods_state(&goods_list);

Keyboard keyboard;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    SD.begin();

    keyboard.Begin();

    LCD::FillScreen(color_black);

    header.Draw();
    footer.Draw();

    goods_state.Begin();
}

void loop()
{
    M5.update();

    keyboard.Update();

    delay(20);
}