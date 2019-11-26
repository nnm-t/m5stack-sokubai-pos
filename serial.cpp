#include "serial.h"

void Serial::Begin()
{
    _serial->begin(_baud_rate);
    _is_ready = true;
}

void Serial::End()
{
    _is_ready = false;
    _serial->end();
}

bool Serial::IsReady()
{
    return _is_ready;
}

void Serial::Print(const char* string)
{
    _serial->print(string);
}

void Serial::Print(const String& string)
{
    _serial->print(string);
}

void Serial::Println(const char* string)
{
    _serial->println(string);
}

void Serial::Println(const String& string)
{
    _serial->println(string);
}