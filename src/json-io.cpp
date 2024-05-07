#include "json-io.h"

void JsonIO::OpenJson(const char* file_name, JsonDocument& json_document)
{
    json_document.clear();

    File file = SD.open(file_name, FILE_READ);

    String json_text;
    json_text.reserve(file.size());

    while (file.available())
    {
        json_text += static_cast<char>(file.read());
    }

    file.close();

    DeserializationError error = deserializeJson(json_document, json_text);

    if (error != DeserializationError::Code::Ok)
    {
        _serial->Print("JSON deserialize failed: ");
        _serial->Println(file_name);
    }
}

void JsonIO::Read()
{
    // ファイルごとにデシリアライズしてJsonArrayへ展開
    StaticJsonDocument<goods_size> json_goods;
    OpenJson(goods_file, json_goods);
    JsonArray goods = json_goods[goods_key].as<JsonArray>();
    JsonArray mac = json_goods[mac_key].as<JsonArray>();

    StaticJsonDocument<sales_size> json_sales;
    OpenJson(sales_file, json_sales);
    JsonArray sales = json_sales[goods_key].as<JsonArray>();
    JsonArray amounts = json_sales[amounts_key].as<JsonArray>();

    _espnow->Deserialize(mac);
    _goods_list->Deserialize(goods, sales);
    _amount_state->Deserialize(amounts);
}

void JsonIO::Write()
{
    // Salesのみシリアライズ
    StaticJsonDocument<sales_size> json_document;

    JsonArray sales = json_document.createNestedArray(goods_key);
    JsonArray amounts = json_document.createNestedArray(amounts_key);

    _goods_list->Serialize(sales);
    _amount_state->Serialize(amounts);

    String json_text;
    serializeJsonPretty(json_document, json_text);

    File file = SD.open(sales_file, FILE_WRITE);
    file.println(json_text);
    file.close();
}