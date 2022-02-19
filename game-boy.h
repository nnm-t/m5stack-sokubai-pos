#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>

#include "keyboard.h"

class GameBoy : public Keyboard
{
    static constexpr const uint8_t up_code = 0xFE;
    static constexpr const uint8_t down_code = 0xFD;
    static constexpr const uint8_t left_code = 0xFB;
    static constexpr const uint8_t right_code = 0xF7;
    static constexpr const uint8_t a_code = 0xEF;
    static constexpr const uint8_t b_code = 0xDF;
    static constexpr const uint8_t start_code = 0x7F;
    static constexpr const uint8_t select_code = 0xBF;
    static constexpr const uint8_t release_code = 0xFF;

    
protected:
    void ReceiveKeyCode(const uint8_t code) override;

public:

    GameBoy() : Keyboard()
    {

    }
};