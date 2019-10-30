#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <M5Stack.h>

// MFRC522_I2C.h, MFRC522_I2C.cpp は .gitignore で除外済み. 別途サンプルからコピーする.
#include "MFRC522_I2C.h"

class RFID
{
    MFRC522 _mfrc522;

public:
    RFID(const uint8_t i2c_address) : _mfrc522(MFRC522(i2c_address))
    {

    }

    void Begin();

    void Update();
};