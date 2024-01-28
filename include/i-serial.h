#pragma once

#include <Arduino.h>
#include <M5Stack.h>

class ISerial
{
public:
    virtual void Begin();

    virtual void End();

    virtual bool IsReady();

    virtual void Print(const char* string) = 0;

    virtual void Print(const String& string) = 0;

    virtual void Println(const char* string) = 0;

    virtual void Println(const String& string) = 0;
};