#pragma once

#include <cmath>

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "vector2.h"
#include "rect.h"
#include "constants.h"
#include "lcd.h"
#include "text-datum.h"
#include "price-place.h"
#include "state-selector.h"

class AmountState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);
    static constexpr const Vector2<int32_t> price_1000_pos = Vector2<int32_t>(125, 120);
    static constexpr const Vector2<int32_t> price_100_pos = Vector2<int32_t>(155, 120);
    static constexpr const Vector2<int32_t> price_lower_pos = Vector2<int32_t>(160, 120);

    static constexpr const Vector2<int32_t> price_rect_pos = Vector2<int32_t>(70, 105);

    static constexpr const Vector2<int32_t> price_place_pos = Vector2<int32_t>(105, 90);

    static constexpr const Vector2<int32_t> price_place_upper0 = Vector2<int32_t>(115, 100);
    static constexpr const Vector2<int32_t> price_place_upper1 = Vector2<int32_t>(105, 90);
    static constexpr const Vector2<int32_t> price_place_upper2 = Vector2<int32_t>(125, 90);

    static constexpr const Vector2<int32_t> price_place_lower0 = Vector2<int32_t>(145, 100);
    static constexpr const Vector2<int32_t> price_place_lower1 = Vector2<int32_t>(135, 90);
    static constexpr const Vector2<int32_t> price_place_lower2 = Vector2<int32_t>(155, 90);

    static constexpr const Rect<int32_t> price_rect = Rect<int32_t>(90, 30);
    static constexpr const Rect<int32_t> price_place_rect = Rect<int32_t>(51, 11);

    static constexpr const int32_t price_max = 9900;
    static constexpr const int32_t price_min = -9900;

    StateSelector* const _selector;

    int32_t _price = 0;
    PricePlace _price_place = PricePlace::Lower;

    void DrawPrice();

    void DrawPricePlace();

public:
    AmountState(StateSelector* const selector) : _selector(selector)
    {

    }

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

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    const int32_t GetPrice()
    {
        return _price;
    }
};