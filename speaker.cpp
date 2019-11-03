#include "speaker.h"

void Speaker::Begin()
{
    M5.Speaker.begin();
}

void Speaker::Tone(const uint16_t frequency, const uint32_t duration_ms)
{
    M5.Speaker.tone(frequency, duration_ms);
}