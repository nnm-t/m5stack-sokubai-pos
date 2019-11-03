#define ESP32

#include <functional>
#include <vector>

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
#include "game-boy.h"
#include "rfid.h"
#include "speaker.h"

using namespace std;

namespace
{
    constexpr const char* json_filename = "/goods.json";
    constexpr const uint8_t mfrc522_address = 0x28;
    constexpr const uint32_t delay_ms = 20;
}


Header header;
Footer footer;
GoodsList goods_list(json_filename);
GoodsState goods_state(&goods_list);

GameBoy gameboy;
Speaker speaker;
RFID rfid(&speaker, mfrc522_address, delay_ms);

void setup()
{
    M5.begin();
    Serial.begin(115200);
    SD.begin();

    gameboy.Begin();
    gameboy.on_up_pressed = [&]{ goods_state.Up(); };
    gameboy.on_down_pressed = [&]{ goods_state.Down(); };
    gameboy.on_left_pressed = [&]{ goods_state.Left(); };
    gameboy.on_right_pressed = [&]{ goods_state.Right(); };
    gameboy.on_select_pressed = [&]{ goods_state.Select(); };

    speaker.Begin();

    rfid.Begin();
    rfid.on_rfid_received = [&](vector<byte> uuid){ goods_state.RFIDReceived(uuid); };

    LCD::FillScreen(color_black);
    LCD::LoadFont(font_20pt);

    header.Draw();
    footer.Draw();

    goods_state.Begin();
}

void loop()
{
    M5.update();

    gameboy.Update();
    rfid.Update();

    delay(delay_ms);
}