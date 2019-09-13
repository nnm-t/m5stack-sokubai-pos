#include "json-goods.h"

namespace SokubaiPos
{
    DeserializationError JsonGoods::Deserialize(String& string)
    {
        return deserializeJson(_json, string);
    }

    bool JsonGoods::IsDeserialized()
    {
        return _is_deserialized;
    }

    Good* JsonGoods::GetGood(const size_t index)
    {
        if (!_is_deserialized)
        {
            return nullptr;
        }

        return &_goods[index];
    }

    Good* JsonGoods::CurrentGood()
    {
        if (!_is_deserialized)
        {
            return nullptr;
        }

        return &_goods[_index];
    }

    Good* JsonGoods::NextGood()
    {
        if (_index >= _goods.size())
        {
            _index = 0;
        }

        return CurrentGood();
    }

    Good* JsonGoods::PrevGood()
    {
        if (_index < 1)
        {
            _index - _goods.size() - 1;
        }

        return CurrentGood();
    }

    size_t JsonGoods::GetIndex() const
    {
        return _index;
    }

    bool JsonGoods::ReadJsonFromFile(const char* path)
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

    bool JsonGoods::ReadJson(String& json_string)
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
}