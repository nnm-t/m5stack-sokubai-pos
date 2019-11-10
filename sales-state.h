#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "footer-text.h"
#include "state-selector.h"

class SalesState : public IState
{
    StateSelector* const _selector;

public:
    SalesState(StateSelector* const selector) : _selector(selector)
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

    void ButtonB() override;

    void ButtonC() override
    {

    }
};