#pragma once

#include <Arduino.h>
#include <M5Stack.h>

#include "i-serial.h"

class Serial : public ISerial
{
    const uint32_t _baud_rate;
    HardwareSerial* const _serial;

    bool _is_ready = false;

public:
    Serial(HardwareSerial* const serial, const uint32_t baud_rate = 115200) :_serial(serial),  _baud_rate(baud_rate)
    {

    }

    void Begin() override;

    void End() override;

    bool IsReady() override;

    void Print(const char* string) override;

    void Print(const String& string) override;

    void Println(const char* string) override;

    void Println(const String& string) override;
};