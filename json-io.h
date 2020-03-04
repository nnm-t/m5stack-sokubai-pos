#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "constants.h"
#include "i-serial.h"
#include "goods-list.h"
#include "amount-state.h"

class JsonIO
{
    static constexpr const char* goods_key = "goods";
    static constexpr const char* amounts_key = "amounts";

    static constexpr const char* goods_file = "goods.json";
    static constexpr const char* sales_file = "sales.json";

    ISerial* const _serial;
    GoodsList* const _goods_list;
    AmountState* const _amount_state;

    StaticJsonDocument<json_size> _json_document = StaticJsonDocument<json_size>();

    JsonDocument& OpenJson(const char* file_name);

public:
    JsonIO(ISerial* const serial, GoodsList* const goods_list, AmountState* const amount_state) : _serial(serial), _goods_list(goods_list), _amount_state(amount_state)
    {

    }

    void Read();

    void Write();
};