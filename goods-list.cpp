#include "goods-list.h"

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