#include "goods-state.h"

using namespace std;

constexpr Vector2<int32_t> GoodsState::title_pos;

constexpr Vector2<int32_t> GoodsState::left_tr0;
constexpr Vector2<int32_t> GoodsState::left_tr1;
constexpr Vector2<int32_t> GoodsState::left_tr2;

constexpr Vector2<int32_t> GoodsState::right_tr0;
constexpr Vector2<int32_t> GoodsState::right_tr1;
constexpr Vector2<int32_t> GoodsState::right_tr2;

FooterText GoodsState::GetFooterText()
{
    return FooterText("金額入力", "売上", "会計");
}

void GoodsState::Begin()
{
    _goods_list->Begin();

    Draw();
}

void GoodsState::Update()
{
    _goods_list->Update();
}

void GoodsState::Draw()
{
    LCD::SetTextColor(color_white, color_black);
    LCD::SetTextDatum(TextDatum::TopLeft);
    LCD::DrawString("商品入力", title_pos);

    LCD::FillRect(bg_pos, bg_rect, color_black);

    LCD::FillTriangle(left_tr0, left_tr1, left_tr2, color_red);
    LCD::FillTriangle(right_tr0, right_tr1, right_tr2, color_red);

    _goods_list->Draw();
}

void GoodsState::Up()
{
    _goods_list->Up();
}

void GoodsState::Down()
{
    _goods_list->Down();
}

void GoodsState::Left()
{
    _goods_list->Prev();
}

void GoodsState::Right()
{
    _goods_list->Next();
}

void GoodsState::Select()
{
    _goods_list->Reset();
}

void GoodsState::Start()
{

}

void GoodsState::ButtonA()
{
    _selector->ToAmountState();
}

void GoodsState::ButtonB()
{
    _selector->ToSalesState();
}

void GoodsState::ButtonC()
{
    _selector->ToPaymentState();
}

void GoodsState::RFIDReceived(const vector<byte>& uuid)
{
    _goods_list->RFIDReceived(uuid);
}

void GoodsState::WriteSales()
{
    // 売上を追加
    _goods_list->WriteSales();
}