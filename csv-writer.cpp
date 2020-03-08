#include "csv-writer.h"

using namespace std;

void CSVWriter::PrintHeader(File& file)
{
    // 日時
    file.print(header_date_time);
    file.print(csv_delimiter);

    // 商品リスト
    for (String name : _goods_list->GetNames())
    {
        file.print(name);
        file.print(csv_delimiter);
    }

    // 金額入力
    file.print(header_amount);

    // 改行
    file.print(return_code);
}

void CSVWriter::PrintQuantities(File& file, DateTime& date_time)
{
    // ファイルが空の時はヘッダを書き込む
    size_t size = file.size();
    if (size == 0)
    {
        PrintHeader(file);
    }

    // 時刻
    file.print(DateTimeToString(date_time));
    file.print(csv_delimiter);

    // 売上
    for (int16_t quantity : _goods_list->GetQuantities())
    {
        file.print(quantity, DEC);
        file.print(csv_delimiter);
    }

    // 金額入力
    file.print(_amount_state->GetPrice(), DEC);

    // 改行
    file.print(return_code);
}

void CSVWriter::WritePayment()
{
    DateTime date_time = _rtc->GetNow();

    // 追記モードで書き込む
    File file = SD.open(csv_name, FILE_APPEND);

    PrintQuantities(file, date_time);

    file.close();
}

String CSVWriter::DateTimeToString(const DateTime& date_time)
{
    return String(date_time.year(), DEC) + "/" + String(date_time.month(), DEC) + "/" + String(date_time.day(), DEC) + " " + String(date_time.hour(), DEC) + ":" + String(date_time.minute(), DEC) + ":" + String(date_time.second(), DEC);
}