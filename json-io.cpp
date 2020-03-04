#include "json-io.h"

JsonDocument& JsonIO::OpenJson(const char* file_name)
{
    _json_document.clear();

    File file = SD.open(file_name, FILE_READ);

    String json_text;
    json_text.reserve(file.size());

    while (file.available())
    {
        json_text += static_cast<char>(file.read());
    }

    file.close();

    DeserializationError error = deserializeJson(_json_document, json_text);

    if (error != DeserializationError::Code::Ok)
    {
        _serial->Print("JSON deserialize failed: ");
        _serial->Println(file_name);
        return _json_document;
    }

    return _json_document;
}

void JsonIO::Read()
{
    // todo: goods.json, sales.json に分離
    auto json_goods = OpenJson(goods_file);
    auto json_sales = OpenJson(sales_file);

    JsonArray goods = json_goods[goods_key].as<JsonArray>();
    JsonArray sales = json_sales[goods_key].as<JsonArray>();
    JsonArray amounts = json_sales[amounts_key].as<JsonArray>();

    _goods_list->Deserialize(goods, sales);
    _amount_state->Deserialize(amounts);
}

void JsonIO::Write()
{
    _json_document.clear();

    JsonArray sales = _json_document.createNestedArray(goods_key);
    JsonArray amounts = _json_document.createNestedArray(amounts_key);

    _goods_list->Serialize(sales);
    _amount_state->Serialize(amounts);

    String json_text;
    serializeJsonPretty(_json_document, json_text);

    File file = SD.open(sales_file, FILE_WRITE);
    file.println(json_text);
    file.close();
}