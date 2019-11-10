#include "sales-state.h"

FooterText SalesState::GetFooterText()
{
    return FooterText("商品入力", "金額入力", String());
}

void SalesState::Draw()
{

}

void SalesState::ButtonA()
{
    _selector->ToGoodsState();
}

void SalesState::ButtonB()
{
    _selector->ToAmountState();
}