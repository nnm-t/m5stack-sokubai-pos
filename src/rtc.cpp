#include "rtc.h"

void RTC::Begin()
{
    _rtc.begin();
}

bool RTC::IsInitialized()
{
    return _rtc.initialized();
}

DateTime RTC::GetNow()
{
    return _rtc.now();
}

void RTC::Adjust(const DateTime& date_time)
{
    _rtc.adjust(date_time);
}