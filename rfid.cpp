#include "rfid.h"

using namespace std;

void RFID::Begin()
{
    Wire.begin();

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

    for (uint16_t i = 0; i < length; i++)
    {
        byte uuid_byte = _mfrc522.uid.uidByte[i];
        uuid.push_back(uuid_byte);

        String output;
        if (uuid_byte < 10)
        {
            output = "0" + String(uuid_byte);
        }
        else 
        {
            output = String(uuid_byte, HEX);
        }
        _serial->Print(output);
    }
    _serial->Print("\n");

    if (on_rfid_received != nullptr)
    {
        on_rfid_received(uuid);
    }
}