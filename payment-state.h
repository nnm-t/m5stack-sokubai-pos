#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "state-selector.h"
#include "amount-state.h"
#include "goods-list.h"
#include "footer-text.h"
#include "constants.h"
#include "lcd.h"
#include "vector2.h"
#include "text-datum.h"
#include "i-serial.h"
#include "speaker.h"
#include "ble-pos-client.h"

class PaymentState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr const int32_t good_x_left = 10;
    static constexpr const int32_t good_x_right = 310;
    static constexpr const int32_t good_y = 60;
    static constexpr const int32_t good_y_span = 20;

    static constexpr const int32_t amount_y = 160;
    static constexpr const int32_t price_y = 190;

    static constexpr const size_t page_goods = 5;

    static constexpr const Vector2<int32_t> amount_left_pos = Vector2<int32_t>(good_x_left, amount_y);
    static constexpr const Vector2<int32_t> amount_right_pos = Vector2<int32_t>(good_x_right, amount_y);

    static constexpr const Vector2<int32_t> price_left_pos = Vector2<int32_t>(good_x_left, price_y);
    static constexpr const Vector2<int32_t> price_right_pos = Vector2<int32_t>(280, price_y);

    static constexpr const Vector2<int32_t> goods_bg_pos = Vector2<int32_t>(good_x_left, good_y);

    static constexpr const Rect<int32_t> goods_bg_rect = Rect<int32_t>(good_x_right - good_x_left, good_y_span * page_goods);

    static constexpr const Rect<int32_t> triangle_rect = Rect<int32_t>(22, 22);

    static constexpr const uint16_t tone_frequency_hz = 440;
    static constexpr const uint32_t tone_duration_ms = 50;

    StateSelector* const _selector;
    AmountState* const _amount_state;
    GoodsList* const _goods_list;
    ISerial* const _serial;
    Speaker* const _speaker;
    BLEPosClient* const _ble_client;

    int32_t _sum_price = 0;
    size_t _page = 0;
    std::vector<size_t> _goods_index;

    void PrintSales();

    void DrawGoods();

    const size_t GetGoodsModifies()
    {
        return _goods_list->GetGoodsModifies();
    }

    const size_t GetGoodsSize()
    {
        return _goods_list->GetGoods().size();
    }

    const size_t GetGoodsPages()
    {
        const size_t modifies = GetGoodsModifies();

        if (modifies <= 0)
        {
            return 1;
        }

        return (GetGoodsModifies() - 1) / page_goods + 1;
    }

public:
    PaymentState(StateSelector* const selector, AmountState* const amount_state, GoodsList* const goods_list, ISerial* const serial, Speaker* const speaker, BLEPosClient* const ble_client) : _selector(selector), _amount_state(amount_state), _goods_list(goods_list), _serial(serial), _goods_index(std::vector<size_t>()), _speaker(speaker), _ble_client(ble_client)
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

    void GameboyA() override
    {
        ButtonC();
    }

    void GameboyB() override
    {
        ButtonA();
    }

    void GameboyReleased() override
    {

    }

    void ButtonA() override;

    void ButtonB() override
    {

    }

    void ButtonC() override;

    void WriteSales() override
    {

    }
};