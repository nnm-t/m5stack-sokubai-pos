#pragma once

#include <functional>
#include <vector>

#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>

// MFRC522_I2C.h, MFRC522_I2C.cpp は .gitignore で除外済み. 別途サンプルからコピーする.
#include "MFRC522_I2C.h"

class RFID
{
    static constexpr const uint32_t min_interval_ms = 1000;

    const uint32_t _delay_ms;

    MFRC522 _mfrc522;
    uint32_t _period_ms = 0;

public:
    std::function<void(std::vector<byte>)> on_rfid_received = nullptr;

    RFID(const uint8_t i2c_address, const uint32_t delay_ms) : _mfrc522(MFRC522(i2c_address)), _delay_ms(delay_ms)
    {

    }

    void Begin();

    void Update();
};