#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"

class StateSelector : public IState
{
    IState* _current = nullptr;
public:
    IState* amount_state = nullptr;
    IState* goods_state = nullptr;

    StateSelector()
    {

    }

    bool IsGoodsState()
    {
        if (goods_state == nullptr)
        {
            return false;
        }

        return _current == goods_state;
    }

    void Begin() override;

    void Update() override
    {

    }

    void Draw() override
    {

    }

    void Left() override;

    void Right() override;

    void Up() override;

    void Down() override;

    void Start() override;

    void Select() override;

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    void ToAmountState();

    void ToGoodsState();
};