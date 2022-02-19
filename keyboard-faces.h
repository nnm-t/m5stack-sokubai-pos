#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>

#include "keyboard.h"

class KeyboardFaces : public Keyboard
{
    static constexpr const uint8_t h_code = 0x68;
    static constexpr const uint8_t j_code = 0x6A;
    static constexpr const uint8_t k_code = 0x6B;
    static constexpr const uint8_t l_code = 0x6C;
    static constexpr const uint8_t space_code = 0x20;
    static constexpr const uint8_t bs_code = 0x08;
    static constexpr const uint8_t enter_code = 0x0A;
    static constexpr const uint8_t del_code = 0x7F;
    static constexpr const uint8_t release_code = 0xFF;

protected:
    virtual void ReceiveKeyCode(uint8_t code) override;
public:
    KeyboardFaces() : Keyboard()
    {

    }
};