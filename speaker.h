#pragma once

#include <Arduino.h>
#include <M5Stack.h>

class Speaker
{
public:
    Speaker()
    {

    }

    void Begin();

    void Tone(const uint16_t frequency, const uint32_t duration_ms);
};