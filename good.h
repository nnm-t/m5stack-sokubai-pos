#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "lcd.h"
#include "constants.h"
#include "sprite.h"

class Good
{
    const static constexpr char* json_name = "name";
    const static constexpr char* json_image = "image_path";
    const static constexpr char* json_price = "price";
    const static constexpr char* json_uuid = "uuid";

    static constexpr const int8_t quantity_max = 20;
    static constexpr const int8_t quantity_min = -20;

    static constexpr Vector2<uint16_t> image_pos = Vector2<uint16_t>(40, 60);
    static constexpr Vector2<int32_t> name_pos = Vector2<int32_t>(170, 70);
    static constexpr Vector2<int32_t> price_pos = Vector2<int32_t>(170, 110);
    static constexpr Vector2<int32_t> qty_pos = Vector2<int32_t>(170, 140);

    static constexpr Rect<int32_t> price_bg_rect = Rect<int32_t>(120, 20);
    static constexpr Rect<int32_t> qty_bg_rect = Rect<int32_t>(90, 20);

    String _name;
    String _image_path;

    int8_t _quantity = 0;

    const int32_t _price;
    const std::vector<byte> _uuid;

    void UpdateQuantity();

public:
    Good(String& name, String& image_path, const int32_t price, const std::vector<byte>& uuid) : _name(name), _image_path(image_path), _price(price), _uuid(uuid)
    {
    }

    void Draw(Sprite* const sprite);

    static Good Deserialize(JsonVariant& json);

    const int32_t GetPrice() const
    {
        return _price;
    }

    const int32_t GetSumPrice()
    {
        return _price * _quantity;
    }

    const std::vector<byte>& GetUUID()
    {
        return _uuid;
    }

    const bool IsMatchUUID(const std::vector<byte>& uuid);

    void Up();

    void Down();

    void Reset();
};