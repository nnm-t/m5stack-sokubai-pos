#include "bluetooth-spp.h"

bool BluetoothSPP::Begin(const char* local_name, const bool is_master)
{
    return _serial.begin(local_name, is_master);
}

bool BluetoothSPP::Begin(const String& local_name, const bool is_master)
{
    return _serial.begin(local_name, is_master);
}

void BluetoothSPP::Print(const char* string)
{
    _serial.print(string);
}

void BluetoothSPP::Print(const String& string)
{
    _serial.print(string);
}

void BluetoothSPP::Println(const char* string)
{
    _serial.println(string);
}

void BluetoothSPP::Println(const String& string)
{
    _serial.println(string);
}