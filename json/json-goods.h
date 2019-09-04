#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "../sokubai-pos.h"
#include "good.h"

namespace SokubaiPos
{
    class JsonGoods
    {
        StaticJsonDocument<4096> _json;
        std::vector<Good> _goods;

        DeserializationError Deserialize(String& string)
        {
            return deserializeJson(_json, string);
        }

    public:
        JsonGoods()
        : _json(StaticJsonDocument<4096>()), _goods(std::vector<Good>())
        {

        }

        bool ReadJson(String& json_string)
        {
            if (Deserialize(json_string) != DeserializationError::Ok)
            {
                return false;
            }

            JsonArray array = _json.as<JsonArray>();

            for (JsonVariant element : array)
            {
                Good good = Good::FromJson(element);
                _goods.push_back(good);
            }

            return true;
        }
    };
}