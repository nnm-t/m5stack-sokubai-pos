#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "state-selector.h"
#include "footer-text.h"
#include "constants.h"
#include "lcd.h"
#include "vector2.h"
#include "text-datum.h"

class PaymentState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);
    static constexpr const Vector2<int32_t> amount_pos = Vector2<int32_t>(310, 190);

    StateSelector* const _selector;

public:
    PaymentState(StateSelector* const selector) : _selector(selector)
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

    void Up() override
    {

    }

    void Down() override
    {

    }

    void Left() override
    {

    }

    void Right() override
    {

    }

    void Select() override
    {

    }

    void Start() override
    {

    }

    void ButtonA() override;

    void ButtonB() override
    {

    }

    void ButtonC() override;
};