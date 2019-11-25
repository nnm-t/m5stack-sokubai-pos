#include "serial.h"

void Serial::Begin(const uint32_t baud_rate)
{
    _serial->begin(baud_rate);
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