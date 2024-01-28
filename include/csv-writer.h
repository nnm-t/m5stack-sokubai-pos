#pragma once

#include <vector>

#include <Arduino.h>
#include <M5Stack.h>

#include "goods-list.h"
#include "amount-state.h"
#include "rtc.h"

class CSVWriter
{
    static constexpr const char* csv_name = "/sales.csv";

    static constexpr const char* csv_delimiter = ",";
    static constexpr const char* return_code = "\n";

    static constexpr const char* header_date_time = "日時";
    static constexpr const char* header_amount = "金額入力";

    RTC* const _rtc;
    GoodsList* const _goods_list;
    AmountState* const _amount_state;

    void PrintHeader(File& file);

    void PrintQuantities(File& file, DateTime& date_time);

    static String DateTimeToString(const DateTime& date_time);

public:
    CSVWriter(RTC* const rtc, GoodsList* const goods_list, AmountState* const amount_state) : _rtc(rtc), _goods_list(goods_list), _amount_state(amount_state)
    {

    }

    void WritePayment();
};