#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

namespace SokubaiPos
{
    class Good
    {
        // 120x120
        const Vector2<uint16_t> image_pos = Vector2<uint16_t>(40, 60);

        const Vector2<int32_t> name_pos = Vector2<int32_t>(170, 60);
        const Vector2<int32_t> price_pos = Vector2<int32_t>(170, 100);
        const Vector2<int32_t> qty_pos = Vector2<int32_t>(170, 140);

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

            Text price_text(40);
            price_text.LoadFont(font_40pt);
            price_text.Draw(_name, price_pos);

            Text qty_text(20);
            qty_text.LoadFont(font_20pt);
            qty_text.Draw("数量: " + String(_qty), qty_pos);
        }

        uint32_t GetPrice()
        {
            return _price;
        }

        String GetName()
        {
            return _name;
        }

        String GetImagePath()
        {
            return _image_path;
        }
    };
}