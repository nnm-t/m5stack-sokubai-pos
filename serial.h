#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-serial.h"

class Serial : public ISerial
{
    HardwareSerial* const _serial;

public:
    Serial(HardwareSerial* const serial) : _serial(serial)
    {

    }

    void Begin(const uint32_t baud_rate = 115200);

    void Print(const char* string) override;

    void Print(const String& string) override;

    void Println(const char* string) override;

    void Println(const String& string) override;
};