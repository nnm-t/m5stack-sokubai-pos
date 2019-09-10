#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "../constants.h"
#include "good.h"

namespace SokubaiPos
{
    class JsonGoods
    {
        StaticJsonDocument<4096> _json;
        std::vector<Good> _goods;

        size_t _index = 0;
        bool _is_deserialized = false;

        DeserializationError Deserialize(String& string)
        {
            return deserializeJson(_json, string);
        }

    public:
        JsonGoods()
        : _json(StaticJsonDocument<4096>()), _goods(std::vector<Good>())
        {

        }

        bool IsDeserialized()
        {
            return _is_deserialized;
        }

        Good* GetGood(const size_t index)
        {
            if (!_is_deserialized)
            {
                return nullptr;
            }

            return &_goods[index];
        }

        Good* CurrentGood()
        {
            if (!_is_deserialized)
            {
                return nullptr;
            }

            return &_goods[_index];
        }

        Good* NextGood()
        {
            if (_index >= _goods.size())
            {
                _index = 0;
            }

            return CurrentGood();
        }

        Good* PrevGood()
        {
            if (_index < 1)
            {
                _index - _goods.size() - 1;
            }

            return CurrentGood();
        }

        size_t GetIndex() const
        {
            return _index;
        }

        bool ReadJsonFromFile(const char* path)
        {
            File file = SD.open(path, FILE_READ);

            if (!file)
            {
                return false;
            }

            String string = file.readString();
            file.close();

            return ReadJson(string);
        }

        bool ReadJson(String& json_string)
        {
            if (Deserialize(json_string) != DeserializationError::Ok)
            {
                return false;
            }

            _is_deserialized = false;
            _goods.clear();
            JsonArray array = _json.as<JsonArray>();

            for (JsonVariant element : array)
            {
                Good good = Good::FromJson(element);
                _goods.push_back(good);
            }

            if (_goods.size() < 1)
            {
                return false;
            }

            _is_deserialized = true;

            return true;
        }
    };
}