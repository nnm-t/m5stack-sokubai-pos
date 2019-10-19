#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "good.h"

class GoodsList
{
    static constexpr size_t json_size = 1024;

    StaticJsonDocument<json_size> _json_document;
    std::vector<Good> _goods;

public:
    GoodsList() : _json_document(StaticJsonDocument<json_size>()), _goods(std::vector<Good>())
    {

    }

    void Begin(const char* file_name);
};