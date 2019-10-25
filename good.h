#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "lcd.h"
#include "constants.h"

class Good
{
    const static constexpr char* json_name = "name";
    const static constexpr char* json_image = "image_path";
    const static constexpr char* json_price = "price";

    static constexpr Vector2<uint16_t> image_pos = Vector2<uint16_t>(40, 60);
    static constexpr Vector2<int32_t> name_pos = Vector2<int32_t>(170, 60);
    static constexpr Vector2<int32_t> price_pos = Vector2<int32_t>(170, 100);
    static constexpr Vector2<int32_t> qty_pos = Vector2<int32_t>(170, 140);

    String _name;
    String _image_path;

    uint8_t _quantity = 0;

    const uint32_t _price;

public:
    Good(String& name, String& image_path, const uint32_t price) : _name(name), _image_path(image_path), _price(price)
    {

    }

    void Draw();

    static Good Deserialize(JsonVariant& json);

    const uint32_t GetPrice() const
    {
        return _price;
    }
};