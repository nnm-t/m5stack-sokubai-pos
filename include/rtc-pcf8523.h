#pragma once

#include <Arduino.h>
#include <M5Stack.h>

class DateTime
{
    uint8_t yOff;
    uint8_t m;
    uint8_t d;
    uint8_t hh;
    uint8_t mm;
    uint8_t ss;

public:
    DateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour = 0, uint8_t min = 0, uint8_t sec = 0) : yOff(year - 2000), m(month), d(day), hh(hour), mm(min), ss(sec)
    {

    }

    DateTime() : DateTime(2000, 1, 1)
    {

    }

    uint16_t year() const
    {
        return 2000 + yOff;
    }

    uint8_t month() const
    {
        return m;
    }

    uint8_t day() const
    {
        return d;
    }

    uint8_t hour() const
    {
        return hh;
    }

    uint8_t minute() const
    {
        return mm;
    }

    uint8_t second() const
    {
        return ss;
    }
};

class RTC_PCF8523
{
    static constexpr const uint8_t address = 0x68;
    static constexpr const uint8_t register_control3 = 0x02;
    static constexpr const uint8_t standby_mode = 0xE0;

    TwoWire* const _wire;

    static const uint8_t bin2bcd(const uint8_t value);
    static const uint8_t bcd2bin(const uint8_t value);

public:
    RTC_PCF8523(TwoWire* const wire = &Wire1) : _wire(wire)
    {

    }

    const bool begin(const uint8_t sda = 26, const uint8_t scl = 13);

    const bool initialized();

    DateTime now();

    void adjust(const DateTime& dt);
};