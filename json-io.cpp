#include "json-io.h"

void JsonIO::Read()
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

    JsonArray goods = _json_document[json_goods].as<JsonArray>();
    JsonArray amounts = _json_document[json_amounts].as<JsonArray>();

    _goods_list->Deserialize(goods);
    _amount_state->Deserialize(amounts);
}

void JsonIO::Write()
{
    _json_document.clear();

    JsonArray goods = _json_document.createNestedArray(json_goods);
    JsonArray amounts = _json_document.createNestedArray(json_amounts);

    _goods_list->Serialize(goods);
    _amount_state->Serialize(amounts);

    String json_text;
    serializeJsonPretty(_json_document, json_text);

    File file = SD.open(_file_name, FILE_WRITE);
    file.println(json_text);
    file.close();
}