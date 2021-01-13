#define ESP32

#include <functional>
#include <vector>

#include <M5Stack.h>
#include <Ticker.h>
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
#include "settings-state.h"
#include "game-boy.h"
#include "m5-button.h"
#include "rfid.h"
#include "speaker.h"
#include "json-io.h"
#include "hard-serial.h"
#include "csv-writer.h"
#include "ble-pos-client.h"

using namespace std;

namespace
{
    constexpr const char* bluetooth_name = "M5Stack-Sokubai-POS";
    constexpr const uint8_t mfrc522_address = 0x28;
    constexpr const uint32_t ticker_ms = 20;
    constexpr const uint8_t brightness_initial = 63;
    constexpr const uint8_t brightness_step = 16;
}

Ticker ticker;

HardSerial serial;
RTC rtc;

BLEUUID service_uuid("b8b4f6e7-8e73-4f07-949c-6b813af2c119");
BLEUUID num_characteristic_uuid(static_cast<uint16_t>(0x0000));
BLEUUID price_characteristic_uuid(static_cast<uint16_t>(0x0001));
BLEPosClient ble_client("M5Stack-Sokubai-Pos", service_uuid, num_characteristic_uuid, price_characteristic_uuid);

Header header(&rtc, ticker_ms);
Footer footer;
Speaker speaker;
GoodsList goods_list(&ble_client);

StateSelector selector(&footer);
GoodsState goods_state(&selector, &goods_list);
AmountState amount_state(&selector);
PaymentState payment_state(&selector, &amount_state, &goods_list, &serial, &speaker);
SalesState sales_state(&selector, &amount_state, &goods_list, &serial);

JsonIO json_io(&serial, &goods_list, &amount_state);
CSVWriter csv_writer(&rtc, &goods_list, &amount_state);

GameBoy gameboy;
M5Button m5_button;
RFID rfid(&serial, &speaker, mfrc522_address, ticker_ms);

Brightness brightness(brightness_initial, brightness_step);
SettingsState settings_state(&selector, &rtc, &brightness);

void setup()
{
    M5.begin();
    SD.begin();

    serial.Begin();
    brightness.Begin();
    rtc.Begin();

    selector.goods_state = &goods_state;
    selector.amount_state = &amount_state;
    selector.payment_state = &payment_state;
    selector.sales_state = &sales_state;
    selector.settings_state = &settings_state;
    selector.write_json = [&] { json_io.Write(); };
    selector.write_csv = [&] { csv_writer.WritePayment(); };

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

    header.Begin();
    selector.Begin();

    ble_client.Begin();

    ticker.attach_ms(ticker_ms, OnTimerTicked);
}

void loop()
{

}

void OnTimerTicked()
{
    M5.update();

    header.Update();

    gameboy.Update();
    m5_button.Update();

    selector.Update();

    rfid.Update();

    // todo: 接続処理を手動に変更
    // ble_client.Update()
}