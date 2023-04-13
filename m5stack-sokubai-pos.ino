#include "config.h"

#include <functional>
#include <vector>

#include <M5Stack.h>
#include <Ticker.h>
#include <ArduinoJson.h>
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

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

#ifdef FACES_GAMEBOY
#include "game-boy.h"
#elif FACES_KEYBOARD
#include "keyboard-faces.h"
#endif

#include "m5-button.h"
#include "rfid.h"
#include "neopixel.h"
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

    LGFX lcd;
    Ticker ticker;

    HardSerial serial;
    RTC rtc;
    NeoPixel neopixel;

    BLEUUID service_uuid("1b36fd1e-6fc4-4dc6-8c82-c13552b88789");
    BLEUUID price_characteristic_uuid("4ee58129-a22f-41cd-bdca-4079fe0632d0");
    BLEPosClient ble_client("M5Stack-Sokubai-Pos", service_uuid, price_characteristic_uuid, &serial);

    Header header(&rtc, &ble_client, ticker_ms);
    Footer footer;
    Speaker speaker;
    GoodsList goods_list(&ble_client);
    RFID rfid(&serial, &speaker, mfrc522_address, ticker_ms);

    StateSelector selector(&footer);
    GoodsState goods_state(&selector, &goods_list, &rfid, &neopixel);
    AmountState amount_state(&selector, &ble_client);
    PaymentState payment_state(&selector, &amount_state, &goods_list, &serial, &speaker, &ble_client);
    SalesState sales_state(&selector, &amount_state, &goods_list, &serial);

    JsonIO json_io(&serial, &goods_list, &amount_state);
    CSVWriter csv_writer(&rtc, &goods_list, &amount_state);

    #ifdef FACES_GAMEBOY
    GameBoy panel;
    #elif FACES_KEYBOARD
    KeyboardFaces panel;
    #endif
    M5Button m5_button;

    Brightness brightness(brightness_initial, brightness_step);
    SettingsState settings_state(&selector, &rtc, &brightness, &ble_client, &rfid, ticker_ms);
}

void setup()
{
    LCD::Init(&lcd);
    M5.begin();
    SD.begin();

    serial.Begin();
    brightness.Begin();
    rtc.Begin();
    neopixel.Begin();

    selector.goods_state = &goods_state;
    selector.amount_state = &amount_state;
    selector.payment_state = &payment_state;
    selector.sales_state = &sales_state;
    selector.settings_state = &settings_state;
    selector.write_json = [&] { json_io.Write(); };
    selector.write_csv = [&] { csv_writer.WritePayment(); };

    panel.Begin();
    panel.on_up_pressed = [&]{ selector.Up(); };
    panel.on_down_pressed = [&]{ selector.Down(); };
    panel.on_left_pressed = [&]{ selector.Left(); };
    panel.on_right_pressed = [&]{ selector.Right(); };
    panel.on_start_pressed = [&]{ selector.Start(); };
    panel.on_select_pressed = [&]{ selector.Select(); };
    panel.on_a_pressed = [&]{ selector.GameboyA(); };
    panel.on_b_pressed = [&]{ selector.GameboyB(); };
    panel.on_released = [&]{ selector.GameboyReleased(); };

    m5_button.Begin();
    m5_button.on_button_a_pressed = [&]{ selector.ButtonA(); };
    m5_button.on_button_b_pressed = [&]{ selector.ButtonB(); };
    m5_button.on_button_c_pressed = [&]{ selector.ButtonC(); };

    speaker.Begin();

#ifdef ENABLE_RFID
    rfid.Begin();
    rfid.on_rfid_received = [&](vector<byte> uuid)
    { 
        if (!selector.IsGoodsState())
        {
            return;
        }

        goods_state.RFIDReceived(uuid);
    };
#endif ENABLE_RFID

    json_io.Read();

    LCD::FillScreen(color_black);
    LCD::SetFont(&fonts::lgfxJapanGothic_20);

    header.Begin();
    selector.Begin();

    ble_client.Begin();

    ticker.attach_ms(ticker_ms, OnTimerTicked);
}

void loop()
{
    settings_state.UpdateMainLoop();

    ble_client.Update();
}

void OnTimerTicked()
{
    M5.update();

    header.Update();

    panel.Update();
    m5_button.Update();

    selector.Update();
}