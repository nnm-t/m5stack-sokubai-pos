#pragma once

#include <cmath>
#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include <ArduinoJson.h>

#include "i-state.h"
#include "vector2.h"
#include "rect.h"
#include "constants.h"
#include "lcd.h"
#include "text-datum.h"
#include "price-place.h"
#include "state-selector.h"
#include "esp-now.h"

class AmountState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);
    static constexpr const Vector2<int32_t> title2_pos = Vector2<int32_t>(30, 50);
    static constexpr const Vector2<int32_t> price_1000_pos = Vector2<int32_t>(144, 120);
    static constexpr const Vector2<int32_t> price_100_pos = Vector2<int32_t>(160, 120);
    static constexpr const Vector2<int32_t> price_lower_pos = Vector2<int32_t>(160, 120);

    static constexpr const Vector2<int32_t> price_rect_pos = Vector2<int32_t>(70, 105);

    static constexpr const Vector2<int32_t> price_place_pos = Vector2<int32_t>(116, 84);

    static constexpr const Vector2<int32_t> price_place_upper0 = Vector2<int32_t>(136, 94);
    static constexpr const Vector2<int32_t> price_place_upper1 = Vector2<int32_t>(126, 84);
    static constexpr const Vector2<int32_t> price_place_upper2 = Vector2<int32_t>(146, 84);

    static constexpr const Vector2<int32_t> price_place_lower0 = Vector2<int32_t>(150, 94);
    static constexpr const Vector2<int32_t> price_place_lower1 = Vector2<int32_t>(140, 84);
    static constexpr const Vector2<int32_t> price_place_lower2 = Vector2<int32_t>(160, 84);

    static constexpr const Rect<int32_t> price_rect = Rect<int32_t>(90, 32);
    static constexpr const Rect<int32_t> price_place_rect = Rect<int32_t>(45, 11);

    static constexpr const int32_t price_max = 9900;
    static constexpr const int32_t price_min = -9900;

    StateSelector* const _selector;
    ESPNOW* const _espnow;

    int32_t _price = 0;
    std::vector<int32_t> _amounts;
    PricePlace _price_place = PricePlace::Lower;

    void DrawPrice();

    void DrawPricePlace();

public:
    AmountState(StateSelector* const selector, ESPNOW* const espnow) : _selector(selector), _amounts(std::vector<int32_t>()), _espnow(espnow)
    {

    }

    void Deserialize(JsonArray& json_array);

    void Serialize(JsonArray& json_array);

    FooterText GetFooterText() override;

    void Begin() override
    {

    }

    void Update() override
    {

    }

    void Draw() override;

    void Up() override;

    void Down() override;

    void Left() override;

    void Right() override;

    void Select() override;

    void Start() override
    {

    }

    void GameboyA() override
    {
        Up();
    }

    void GameboyB() override
    {
        Down();
    }

    void GameboyReleased() override
    {

    }

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    void WriteSales() override;

    const int32_t GetPrice()
    {
        return _price;
    }

    std::vector<int32_t>& GetAmounts()
    {
        return _amounts;
    }

    const int32_t GetSumSales();
};