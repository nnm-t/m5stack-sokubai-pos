#define ESP32

#include <M5Stack.h>
#include <Ticker.h>
#include <ArduinoJson.h>

#include "constants.h"
#include "sokubai-pos.h"

using namespace SokubaiPos;

constexpr Rect<uint32_t> tft_rect(320, 240);
constexpr Rect<uint16_t> sprite_rect(32, 32);

Header header;

Diagram footer;
constexpr Vector2<int32_t> footer_left(20, 220);
constexpr Vector2<int32_t> footer_center(120, 220);
constexpr Vector2<int32_t> footer_right(220, 220);
constexpr Rect<int32_t> footer_border(80, 20);

Text footer_text(20, Color16::White(), Color16::Black(), TextDatum::TopCenter);
constexpr Vector2<int32_t> footer_text_left(60, 220);
constexpr Vector2<int32_t> footer_text_center(160, 220);
constexpr Vector2<int32_t> footer_text_right(260, 220);

GoodsState goods_state;
StateBase* state = &goods_state;

void setup()
{
    M5.begin();
    Serial.begin(115200);
    Serial.println(Color16::White().Get());

    LCD::FillScreen(Color16::White());

    header.Begin();

    footer.FillRect(Vector2<int32_t>(0, 220), Rect<int32_t>(320, 20), Color16::Black());
    footer.DrawRect(footer_left, footer_border);
    footer.DrawRect(footer_center, footer_border);
    footer.DrawRect(footer_right, footer_border);

    footer_text.LoadFont("mplus-1c20");
    footer_text.Draw("金額入力", footer_text_left);
    footer_text.Draw("反転", footer_text_center);
    footer_text.Draw("会計", footer_text_right);
}

void loop()
{
    M5.update();

    state->Loop();
}