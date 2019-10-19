#include "goods-list.h"

void GoodsList::Begin(const char* file_name)
{
    File file = SD.open(file_name, FILE_READ);

    if (!file.available())
    {
        Serial.println("JSON not found.");
        return;
    }

    String json_text(file.read());
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
}