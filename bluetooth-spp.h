#pragma once

#include <Arduino.h>
#include <M5Stack.h>
#include <BluetoothSerial.h>

#include "i-serial.h"

class BluetoothSPP : public ISerial
{
    BluetoothSerial _serial;

public:
    BluetoothSPP() : _serial(BluetoothSerial())
    {

    }

    bool Begin(const char* local_name, const bool is_master = false);

    bool Begin(const String& local_name, const bool is_master = false);

    void Print(const char* string) override;

    void Print(const String& string) override;

    void Println(const char* string) override;

    void Println(const String& string) override;
};