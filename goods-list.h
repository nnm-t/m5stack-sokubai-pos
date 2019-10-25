#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "good.h"

class GoodsList
{
    static constexpr size_t json_size = 1024;

    const char* _file_name;

    StaticJsonDocument<json_size> _json_document;
    std::vector<Good> _goods;

    size_t _current;

    size_t GetLastIndex()
    {
        return _goods.size() - 1;
    }

public:
    GoodsList(const char* file_name) : _file_name(file_name), _json_document(StaticJsonDocument<json_size>()), _goods(std::vector<Good>()), _current(0)
    {

    }

    void Begin();

    void Draw();

    void Next();

    void Prev();

    size_t GetCurrentIndex()
    {
        return _current;
    }
};