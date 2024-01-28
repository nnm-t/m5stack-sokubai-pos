#pragma once

#include <Arduino.h>
#include <M5Stack.h>
#include <BluetoothSerial.h>

#include "i-serial.h"

class BluetoothSPP : public ISerial
{
    const char* _local_name;
    const bool _is_master;

    BluetoothSerial _serial;

public:
    BluetoothSPP(const char* local_name, const bool is_master = false) : _local_name(local_name), _is_master(is_master), _serial(BluetoothSerial())
    {

    }

    BluetoothSPP(const String& local_name, const bool is_master = false) : _local_name(local_name.c_str()), _is_master(is_master), _serial(BluetoothSerial())
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