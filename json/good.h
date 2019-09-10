#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "../misc/vector2.h"
#include "../constants.h"
#include "../m5wrap/lcd.h"

namespace SokubaiPos
{
    class Good
    {
        // 120x120
        static constexpr Vector2<uint16_t> image_pos = Vector2<uint16_t>(40, 60);

        static constexpr Vector2<int32_t> name_pos = Vector2<int32_t>(170, 60);
        static constexpr Vector2<int32_t> price_pos = Vector2<int32_t>(170, 100);
        static constexpr Vector2<int32_t> qty_pos = Vector2<int32_t>(170, 140);

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

        static Good FromJson(JsonVariant& json)
        {
            String name = json["name"].as<String>();
            String image_path = json["image_path"].as<String>();
            uint32_t price = json["price"].as<uint32_t>();

            return Good(price, name, image_path);
        }

        void Draw()
        {
            LCD::DrawBitmapFile(_image_path.c_str(), image_pos);

            Text price_text(40, color_black, color_white);
            price_text.LoadFont(font_40pt);
            price_text.Draw(_name, price_pos);

            Text qty_text(20, color_black, color_white);
            qty_text.LoadFont(font_20pt);
            qty_text.Draw("数量: " + String(_qty), qty_pos);
        }

        uint32_t GetPrice() const
        {
            return _price;
        }

        String GetName() const
        {
            return _name;
        }

        String GetImagePath() const
        {
            return _image_path;
        }

        uint8_t GetQuantity() const
        {
            return _qty;
        }

        void IncrementQuantity()
        {
            _qty++;
        }

        void DecrementQuantity()
        {
            _qty--;
        }
    };

    constexpr Vector2<uint16_t> Good::image_pos;
    constexpr Vector2<int32_t> Good::name_pos;
    constexpr Vector2<int32_t> Good::price_pos;
    constexpr Vector2<int32_t> Good::qty_pos;
}