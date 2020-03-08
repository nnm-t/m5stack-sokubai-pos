#pragma once

#include <functional>

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "footer.h"

class StateSelector
{
    Footer* const _footer;

    IState* _current = nullptr;

    void DrawState()
    {
        _footer->Draw(_current->GetFooterText());

        _current->Draw();
    }

public:
    IState* amount_state = nullptr;
    IState* goods_state = nullptr;
    IState* payment_state = nullptr;
    IState* sales_state = nullptr;
    IState* settings_state = nullptr;

    std::function<void()> write_json = nullptr;
    std::function<void()> write_csv = nullptr;

    StateSelector(Footer* const footer) : _footer(footer)
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

    void Begin();

    void Update();

    void Left();

    void Right();

    void Up();

    void Down();

    void Start();

    void Select();

    void GameboyA();

    void GameboyB();

    void ButtonA();

    void ButtonB();

    void ButtonC();

    void ToAmountState();

    void ToGoodsState();

    void ToPaymentState();

    void ToSalesState();

    void ToSettingsState();

    void WriteSales();
};