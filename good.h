#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

class Good
{
    const static constexpr char* json_name = "name";
    const static constexpr char* json_image = "image_path";
    const static constexpr char* json_price = "price";
    String _name;
    String _image_path;
    const uint32_t _price;

public:
    Good(String& name, String& image_path, const uint32_t price) : _name(name), _image_path(image_path), _price(price)
    {

    }

    static Good Deserialize(JsonVariant& json);
};