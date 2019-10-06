#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "vector2.h"
#include "rect.h"
#include "constants.h"
#include "lcd.h"
#include "text.h"

namespace SokubaiPos
{
    class Good
    {
        // 120x120
        static constexpr Vector2<uint16_t> image_pos = Vector2<uint16_t>(40, 60);

        static constexpr Vector2<int32_t> name_pos = Vector2<int32_t>(170, 60);
        static constexpr Vector2<int32_t> price_pos = Vector2<int32_t>(170, 100);
        static constexpr Vector2<int32_t> qty_pos = Vector2<int32_t>(170, 140);

        static constexpr Rect<uint16_t> name_rect = Rect<uint16_t>(140, 30);

        uint32_t _price;
        String _name;
        String _image_path;

        uint8_t _qty = 0;

    public:
        Good() : _price(0), _name(String()), _image_path(String())
        {

        }

        Good(const uint32_t price, String& name, String& image_path)
        : _price(price), _name(name), _image_path(image_path)
        {

        }

        static Good FromJson(JsonVariant& json);

        void Draw();

        uint32_t GetPrice() const;

        String GetName() const;

        String GetImagePath() const;

        uint8_t GetQuantity() const;

        void IncrementQuantity();

        void DecrementQuantity();
    };
}