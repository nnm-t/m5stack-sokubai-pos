#include "hard-serial.h"

void HardSerial::Begin()
{
    _serial->begin(_baud_rate);
    _is_ready = true;
}

void HardSerial::End()
{
    _is_ready = false;
    _serial->end();
}

bool HardSerial::IsReady()
{
    return _is_ready;
}

void HardSerial::Print(const char* string)
{
    _serial->print(string);
}

void HardSerial::Print(const String& string)
{
    _serial->print(string);
}

void HardSerial::Println(const char* string)
{
    _serial->println(string);
}

void HardSerial::Println(const String& string)
{
    _serial->println(string);
}