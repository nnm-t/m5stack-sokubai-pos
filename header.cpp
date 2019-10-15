#include "header.h"

constexpr Vector2<int32_t> Header::battery_pos;
constexpr Vector2<int32_t> Header::wifi_pos;

void Header::Draw()
{
    M5.Lcd.loadFont(font_20pt, SD);

    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.drawString(WiFi.macAddress(), wifi_pos.X(), wifi_pos.Y());

    M5.Lcd.setTextDatum(TR_DATUM);
    String battery_level(M5.Power.getBatteryLevel());
    M5.Lcd.drawString(battery_level + "%", battery_pos.X(), battery_pos.Y());
}