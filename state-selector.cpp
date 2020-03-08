#include "state-selector.h"

void StateSelector::Begin()
{
    _current = goods_state;

    _footer->Draw(_current->GetFooterText());
    _current->Begin();
}

void StateSelector::Update()
{
    if (_current == nullptr)
    {
        return;
    }

    _current->Update();
}
void StateSelector::Left()
{
    _current->Left();
}

void StateSelector::Right()
{
    _current->Right();
}

void StateSelector::Up()
{
    _current->Up();
}

void StateSelector::Down()
{
    _current->Down();
}

void StateSelector::Start()
{
    if (_current == settings_state)
    {
        // GoodsStateへ戻る
        ToGoodsState();
        return;
    }

    // SettingsStateへ移動
    ToSettingsState();
}

void StateSelector::Select()
{
    _current->Select();
}

void StateSelector::GameboyA()
{
    _current->GameboyA();
}

void StateSelector::GameboyB()
{
    _current->GameboyB();
}

void StateSelector::ButtonA()
{
    _current->ButtonA();
}

void StateSelector::ButtonB()
{
    _current->ButtonB();
}

void StateSelector::ButtonC()
{
    _current->ButtonC();
}

void StateSelector::ToAmountState()
{
    _current = amount_state;
    DrawState();
}

void StateSelector::ToGoodsState()
{
    _current = goods_state;
    DrawState();
}

void StateSelector::ToPaymentState()
{
    _current = payment_state;
    DrawState();
}

void StateSelector::ToSalesState()
{
    _current = sales_state;
    DrawState();
}

void StateSelector::ToSettingsState()
{
    _current = settings_state;
    DrawState();
}

void StateSelector::WriteSales()
{
    // 数量書き出し
    if (write_csv != nullptr)
    {
        write_csv();
    }

    // 売上記録
    if (goods_state != nullptr)
    {
        goods_state->WriteSales();
    }
    if (amount_state != nullptr)
    {
        amount_state->WriteSales();
    }

    if (write_json == nullptr)
    {
        return;
    }

    // 売上合計書き出し
    write_json();
}