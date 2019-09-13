#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "constants.h"
#include "good.h"

namespace SokubaiPos
{
    class JsonGoods
    {
        StaticJsonDocument<4096> _json;
        std::vector<Good> _goods;

        size_t _index = 0;
        bool _is_deserialized = false;

        DeserializationError Deserialize(String& string);

    public:
        JsonGoods()
        : _json(StaticJsonDocument<4096>()), _goods(std::vector<Good>())
        {

        }

        bool IsDeserialized();

        Good* GetGood(const size_t index);

        Good* CurrentGood();

        Good* NextGood();

        Good* PrevGood();

        size_t GetIndex() const;

        bool ReadJsonFromFile(const char* path);

        bool ReadJson(String& json_string);
    };
}