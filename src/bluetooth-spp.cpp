#include "bluetooth-spp.h"

void BluetoothSPP::Begin()
{
    _serial.begin(_local_name, _is_master);
}

void BluetoothSPP::End()
{
    _serial.end();
}

bool BluetoothSPP::IsReady()
{
    return _serial.isReady();
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