#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "constants.h"
#include "i-serial.h"
#include "goods-list.h"
#include "amount-state.h"
#include "esp-now.h"

class JsonIO
{
    static constexpr const size_t goods_size = 3072;
    static constexpr const size_t sales_size = 1024;

    static constexpr const char* goods_key = "goods";
    static constexpr const char* mac_key = "esp-now";
    static constexpr const char* amounts_key = "amounts";

    static constexpr const char* goods_file = "/goods.json";
    static constexpr const char* sales_file = "/sales.json";

    ISerial* const _serial;
    GoodsList* const _goods_list;
    AmountState* const _amount_state;
    ESPNOW* const _espnow;

    void OpenJson(const char* file_name, JsonDocument& json_document);

public:
    JsonIO(ISerial* const serial, GoodsList* const goods_list, AmountState* const amount_state, ESPNOW* const espnow) : _serial(serial), _goods_list(goods_list), _amount_state(amount_state), _espnow(espnow)
    {

    }

    void Read();

    void Write();
};