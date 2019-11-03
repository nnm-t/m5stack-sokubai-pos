#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "good.h"
#include "lcd.h"
#include "constants.h"

class GoodsList
{
    static constexpr size_t json_size = 1024;

    static constexpr Vector2<int32_t> sum_pos = Vector2<int32_t>(170, 190);
    static constexpr Vector2<int32_t> sum_rect_pos = Vector2<int32_t>(170, 189);
    static constexpr Rect<int32_t> sum_rect = Rect<int32_t>(150, 21);

    const char* _file_name;

    StaticJsonDocument<json_size> _json_document;
    std::vector<Good> _goods;

    size_t _current;

    size_t GetLastIndex()
    {
        return _goods.size() - 1;
    }

public:
    GoodsList(const char* file_name) : _file_name(file_name), _json_document(StaticJsonDocument<json_size>()), _goods(std::vector<Good>()), _current(0)
    {

    }

    void Begin();

    void Draw();

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
};