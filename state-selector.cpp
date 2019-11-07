#include "state-selector.h"

void StateSelector::Begin()
{
    _current = goods_state;
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
    _current->Start();
}

void StateSelector::Select()
{
    _current->Select();
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
    _current->Draw();
}

void StateSelector::ToGoodsState()
{
    _current = goods_state;
    _current->Draw();
}