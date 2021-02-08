#include "rtc-pcf8523.h"

const uint8_t RTC_PCF8523::bin2bcd(const uint8_t value)
{
    return value + 6 * (value / 10);
}

const uint8_t RTC_PCF8523::bcd2bin(const uint8_t value)
{
    return value - 6 * (value >> 4);
}

const bool RTC_PCF8523::begin(const uint8_t sda, const uint8_t scl)
{
    _wire->begin(sda, scl);
    _wire->beginTransmission(address);
    if (_wire->endTransmission() == 0)
    {
        return true;
    }

    return false;
}

const bool RTC_PCF8523::initialized()
{
    _wire->beginTransmission(address);
    _wire->write(register_control3);
    _wire->endTransmission();

    _wire->requestFrom(address, 1);
    uint8_t ss = _wire->read();
    return (ss & standby_mode) !=  standby_mode;
}

DateTime RTC_PCF8523::now()
{
    _wire->beginTransmission(address);
    _wire->write(3);
    _wire->endTransmission();

    _wire->requestFrom(address, 7);
    uint8_t ss = bcd2bin(_wire->read() & 0x7F);
    uint8_t mm = bcd2bin(_wire->read());
    uint8_t hh = bcd2bin(_wire->read());
    uint8_t d = bcd2bin(_wire->read());
    _wire->read();
    uint8_t m = bcd2bin(_wire->read());
    uint16_t y = bcd2bin(_wire->read()) + 2000;

    return DateTime(y, m, d, hh, mm, ss);
}

void RTC_PCF8523::adjust(const DateTime& dt)
{
    _wire->beginTransmission(address);
    _wire->write(3);
    _wire->write(bin2bcd(dt.second()));
    _wire->write(bin2bcd(dt.minute()));
    _wire->write(bin2bcd(dt.hour()));
    _wire->write(bin2bcd(0));
    _wire->write(bin2bcd(dt.day()));
    _wire->write(bin2bcd(dt.month()));
    _wire->write(bin2bcd(dt.year() - 2000));
    _wire->endTransmission();

    _wire->beginTransmission(address);
    _wire->write(register_control3);
    _wire->write(0x00);
    _wire->endTransmission();
}