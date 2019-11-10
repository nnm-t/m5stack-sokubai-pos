#include "goods-list.h"

using namespace std;

constexpr Vector2<int32_t> GoodsList::sum_pos;
constexpr Vector2<int32_t> GoodsList::sum_rect_pos;
constexpr Rect<int32_t> GoodsList::sum_rect;

void GoodsList::Begin()
{
    File file = SD.open(_file_name, FILE_READ);

    String json_text;

    while (file.available())
    {
        json_text += static_cast<char>(file.read());
    }

    file.close();

    DeserializationError error = deserializeJson(_json_document, json_text);

    if (error != DeserializationError::Code::Ok)
    {
        Serial.println("JSON deserialize failed.");
        return;
    }

    JsonArray json_array = _json_document.as<JsonArray>();

    for (JsonVariant json_variant : json_array)
    {
        _goods.push_back(Good::Deserialize(json_variant));
    }

    Draw();
}

void GoodsList::Draw()
{
    if (_goods.size() < 1)
    {
        return;
    }

    _goods[_current].Draw();
    DrawSumPrice();
}

void GoodsList::Next()
{
    if (_current >= GetLastIndex())
    {
        _current = 0;
    }
    else
    {
        _current++;
    }

    Draw();
}

void GoodsList::Prev()
{
    if (_current <= 0)
    {
        _current = GetLastIndex();
    }
    else
    {
        _current--;
    }

    Draw();
}

void GoodsList::Up()
{
    _goods[_current].Up();
    DrawSumPrice();
}

void GoodsList::Down()
{
    _goods[_current].Down();
    DrawSumPrice();
}

void GoodsList::DrawSumPrice()
{
    int32_t sum = 0;

    for (Good& good : _goods)
    {
        sum += good.GetSumPrice();
    }

    LCD::SetTextColor(color_yellow, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);

    LCD::FillRect(sum_rect_pos, sum_rect, color_black);
    LCD::DrawString("合計: " + String(sum) + "円", sum_pos);
}

void GoodsList::Reset()
{
    for (Good& good : _goods)
    {
        good.Reset();
    }

    DrawSumPrice();
}

void GoodsList::RFIDReceived(const vector<byte>& uuid)
{
    for (size_t i = 0; i < _goods.size(); i++)
    {
        if (_goods[i].IsMatchUUID(uuid))
        {
            _current = i;

            _goods[i].Draw();
            _goods[i].Up();
            DrawSumPrice();

            return;
        }
    }
}