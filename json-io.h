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
    static constexpr const char* json_goods = "goods";
    static constexpr const char* json_amounts = "amounts";

    const char* _file_name;

    ISerial* const _serial;
    GoodsList* const _goods_list;
    AmountState* const _amount_state;

    StaticJsonDocument<json_size> _json_document;

public:
    JsonIO(const char* file_name, ISerial* const serial, GoodsList* const goods_list, AmountState* const amount_state) : _file_name(file_name), _serial(serial), _goods_list(goods_list), _amount_state(amount_state), _json_document(StaticJsonDocument<json_size>())
    {

    }

    void Read();

    void Write();
};