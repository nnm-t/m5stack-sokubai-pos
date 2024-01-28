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
    const static constexpr char* json_sales = "sales";
    const static constexpr char* json_price = "price";
    const static constexpr char* json_uuid = "uuid";

    static constexpr const int8_t quantity_max = 20;
    static constexpr const int8_t quantity_min = -20;
    static constexpr const int16_t name_dx = -2;
    static constexpr const int16_t name_scroll_end = title_rect.Width() * -1;

    static constexpr Vector2<uint16_t> image_pos = Vector2<uint16_t>(40, 60);
    static constexpr Vector2<int32_t> name_pos = Vector2<int32_t>(20, 30);
    static constexpr Vector2<int32_t> name_line_pos = Vector2<int32_t>(20, 50);
    static constexpr Vector2<int32_t> name_line_end_pos = Vector2<int32_t>(300, 50);
    static constexpr Vector2<int32_t> price_title_pos = Vector2<int32_t>(170, 60);
    static constexpr Vector2<int32_t> price_pos = Vector2<int32_t>(280, 60);
    static constexpr Vector2<int32_t> price_rect_pos = Vector2<int32_t>(220, 60);
    static constexpr Vector2<int32_t> qty_pos = Vector2<int32_t>(170, 90);
    static constexpr Vector2<int32_t> qty_num_pos = Vector2<int32_t>(280, 90);
    static constexpr Vector2<int32_t> qty_num_rect_pos = Vector2<int32_t>(220, 90);

    static constexpr Vector2<int32_t> name_rect_pos = Vector2<int32_t>(19, 29);
    static constexpr Rect<int32_t> name_rect = Rect<int32_t>(title_rect.Width() + title_width + 2, title_rect.Height() + 2);
    static constexpr Rect<int32_t> price_bg_rect = Rect<int32_t>(70, 20);
    static constexpr Rect<int32_t> qty_bg_rect = Rect<int32_t>(70, 20);

    String _name;
    String _image_path;

    int16_t _sales;
    int8_t _quantity = 0;

    const int32_t _price;
    const std::vector<byte> _uuid;

    void UpdateQuantity();

public:
    Good(String& name, String& image_path, const int16_t sales, const int32_t price, const std::vector<byte>& uuid) : _name(name), _image_path(image_path), _sales(sales), _price(price), _uuid(uuid)
    {
    }

    void Draw();

    void DrawName();

    void Update();

    static Good Deserialize(JsonVariant& good, JsonVariant& sales);

    int16_t Serialize();

    String GetName()
    {
        return _name;
    }

    const int8_t GetQuantity()
    {
        return _quantity;
    }

    const int16_t GetSales()
    {
        return _sales;
    }

    const int32_t GetSumSales()
    {
        return _price * _sales;
    }

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

    void WriteSales();
};