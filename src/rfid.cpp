#include "rfid.h"

using namespace std;

void RFID::Begin()
{
    Wire.beginTransmission(_i2c_address);
    const uint8_t error = Wire.endTransmission();

    if (error != 0)
    {
        _is_found = false;
        return;
    }

    _is_found = true;
    _mfrc522.PCD_Init();
}

void RFID::Update()
{
    if (_period_ms < min_interval_ms)
    {
        _period_ms += _delay_ms;
        return;
    }

    _period_ms = 0;

    if (!_is_found)
    {
        return;
    }

    if(!_mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    if (!_mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    _speaker->Tone(tone_frequency_hz, tone_duration_ms);

    const uint16_t length = _mfrc522.uid.size;
    vector<byte> uuid;
    uuid.reserve(length);

    _serial->Print("RFID: ");
    _uuid_string = "";

    for (uint16_t i = 0; i < length; i++)
    {
        byte uuid_byte = _mfrc522.uid.uidByte[i];
        uuid.push_back(uuid_byte);

        if (uuid_byte < 10)
        {
            _uuid_string += "0" + String(uuid_byte);
        }
        else 
        {
            _uuid_string += String(uuid_byte, HEX);
        }

        if (i < length - 1)
        {
            _uuid_string += ":";
        }
    }
    _serial->Print(_uuid_string);
    _serial->Print("\n");

    if (on_rfid_received != nullptr)
    {
        on_rfid_received(uuid);
    }
}