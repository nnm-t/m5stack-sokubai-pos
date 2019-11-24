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
#include "i-state.h"
#include "goods-list.h"
#include "state-selector.h"
#include "goods-state.h"
#include "amount-state.h"
#include "payment-state.h"
#include "sales-state.h"
#include "game-boy.h"
#include "m5-button.h"
#include "rfid.h"
#include "speaker.h"
#include "json-io.h"

using namespace std;

namespace
{
    constexpr const char* json_filename = "/goods.json";
    constexpr const uint8_t mfrc522_address = 0x28;
    constexpr const uint32_t delay_ms = 20;
}

Header header;
Footer footer;
Sprite name_sprite;
GoodsList goods_list(&name_sprite);

StateSelector selector(&footer);
GoodsState goods_state(&selector, &goods_list);
AmountState amount_state(&selector);
PaymentState payment_state(&selector, &amount_state, &goods_list);
SalesState sales_state(&selector);

JsonIO json_io(json_filename, &goods_list, &amount_state);

GameBoy gameboy;
Speaker speaker;
M5Button m5_button;
RFID rfid(&speaker, mfrc522_address, delay_ms);

void setup()
{
    M5.begin();
    Serial.begin(115200);
    SD.begin();

    selector.goods_state = &goods_state;
    selector.amount_state = &amount_state;
    selector.payment_state = &payment_state;
    selector.sales_state = &sales_state;
    selector.write_json = [&]{ json_io.Write(); };

    gameboy.Begin();
    gameboy.on_up_pressed = [&]{ selector.Up(); };
    gameboy.on_down_pressed = [&]{ selector.Down(); };
    gameboy.on_left_pressed = [&]{ selector.Left(); };
    gameboy.on_right_pressed = [&]{ selector.Right(); };
    gameboy.on_start_pressed = [&]{ selector.Start(); };
    gameboy.on_select_pressed = [&]{ selector.Select(); };
    gameboy.on_a_pressed = [&]{ selector.GameboyA(); };
    gameboy.on_b_pressed = [&]{ selector.GameboyB(); };

    m5_button.Begin();
    m5_button.on_button_a_pressed = [&]{ selector.ButtonA(); };
    m5_button.on_button_b_pressed = [&]{ selector.ButtonB(); };
    m5_button.on_button_c_pressed = [&]{ selector.ButtonC(); };

    speaker.Begin();

    rfid.Begin();
    rfid.on_rfid_received = [&](vector<byte> uuid)
    { 
        if (!selector.IsGoodsState())
        {
            return;
        }

        goods_state.RFIDReceived(uuid);
    };

    json_io.Read();

    LCD::FillScreen(color_black);
    LCD::LoadFont(font_20pt);

    header.Draw();
    selector.Begin();

}

void loop()
{
    M5.update();

    gameboy.Update();
    m5_button.Update();
    selector.Update();
    rfid.Update();

    delay(delay_ms);
}