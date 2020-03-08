#pragma once

#include <functional>
#include <vector>

#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>

// MFRC522_I2C.h, MFRC522_I2C.cpp は .gitignore で除外済み. 別途サンプルからコピーする.
#include "MFRC522_I2C.h"

#include "i-serial.h"
#include "speaker.h"
#include "constants.h"

class RFID
{
    static constexpr const uint32_t min_interval_ms = 1000;
    static constexpr const uint16_t tone_frequency_hz = 440;
    static constexpr const uint32_t tone_duration_ms = 50;

    ISerial* const _serial;
    Speaker* const _speaker;

    const uint32_t _delay_ms;

    MFRC522 _mfrc522;
    uint32_t _period_ms = 0;

public:
    std::function<void(std::vector<byte>)> on_rfid_received = nullptr;

    RFID(ISerial* const serial, Speaker* const speaker, const uint8_t i2c_address, const uint32_t delay_ms) : _serial(serial), _speaker(speaker), _mfrc522(MFRC522(i2c_address)), _delay_ms(delay_ms)
    {

    }

    void Begin();

    void Update();
};