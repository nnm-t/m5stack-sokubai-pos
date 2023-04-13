#pragma once

#include "config.h"

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include "i-state.h"
#include "goods-list.h"
#include "lcd.h"
#include "vector2.h"
#include "constants.h"
#include "state-selector.h"
#include "rfid.h"
#include "neopixel.h"

class GoodsState : public IState
{
    static constexpr const Vector2<int32_t> title_pos = Vector2<int32_t>(10, 30);

    static constexpr const Vector2<int32_t> left_tr0 = Vector2<int32_t>(30, 105);
    static constexpr const Vector2<int32_t> left_tr1 = Vector2<int32_t>(10, 120);
    static constexpr const Vector2<int32_t> left_tr2 = Vector2<int32_t>(30, 135);

    static constexpr const Vector2<int32_t> right_tr0 = Vector2<int32_t>(290, 105);
    static constexpr const Vector2<int32_t> right_tr1 = Vector2<int32_t>(310, 120);
    static constexpr const Vector2<int32_t> right_tr2 = Vector2<int32_t>(290, 135);

    static constexpr const uint32_t neopixel_color = 0xFF9900;
    static constexpr const uint32_t neopixel_brightness = 0x0F;

    StateSelector* const _selector;
    GoodsList* const _goods_list;
    RFID* const _rfid;
    NeoPixel* const _neopixel;

    bool _is_gameboy_a_press = false;

public:
    GoodsState(StateSelector* const selector, GoodsList* const goods_list, RFID* const rfid, NeoPixel* const neopixel) : _selector(selector), _goods_list(goods_list), _rfid(rfid), _neopixel(neopixel)
    {

    }

    FooterText GetFooterText() override;

    void Begin() override;

    void Update() override;

    void Draw() override;

    void Up() override;

    void Down() override;

    void Left() override;

    void Right() override;

    void Select() override;

    void Start() override;

    void GameboyA() override;

    void GameboyB() override
    {

    }

    void GameboyReleased() override;

    void ButtonA() override;

    void ButtonB() override;

    void ButtonC() override;

    void RFIDReceived(const std::vector<byte>& uuid);

    void WriteSales() override;
};