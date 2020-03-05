#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "good.h"
#include "lcd.h"
#include "constants.h"
#include "sprite.h"

class GoodsList
{
    static constexpr Vector2<int32_t> sum_pos = Vector2<int32_t>(170, 190);
    static constexpr Vector2<int32_t> sum_rect_pos = Vector2<int32_t>(170, 189);

    static constexpr Rect<int16_t> name_rect = Rect<int16_t>(title_rect.Width() + title_width, title_rect.Height());
    static constexpr Rect<int32_t> sum_rect = Rect<int32_t>(150, 21);

    std::vector<Good> _goods;
    Sprite* const _sprite;

    size_t _current;

    size_t GetLastIndex()
    {
        return _goods.size() - 1;
    }

    void BeginSprite();

public:
    GoodsList(Sprite* const sprite) : _sprite(sprite), _goods(std::vector<Good>()), _current(0)
    {

    }

    void Deserialize(JsonArray& json_goods, JsonArray& json_sales);

    void Serialize(JsonArray& json_array);

    void Begin();

    void Draw();

    void Update();

    void Next();

    void Prev();

    void Up();

    void Down();

    void Reset();

    void RFIDReceived(const std::vector<byte>& uuid);

    void DrawSumPrice();

    size_t GetCurrentIndex()
    {
        return _current;
    }

    std::vector<Good>& GetGoods()
    {
        return _goods;
    }

    const size_t GetGoodsModifies()
    {
        size_t modifies = 0;

        for (Good& good: _goods)
        {
            if (good.GetQuantity() != 1)
            {
                modifies++;
            }
        }

        return modifies;
    }

    void WriteSales();
};