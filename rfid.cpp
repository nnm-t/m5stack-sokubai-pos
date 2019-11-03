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

    if(!_mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    if (!_mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    _speaker->Tone(tone_frequency_ms, tone_duration_ms);

    uint16_t length = _mfrc522.uid.size;
    vector<byte> uuid;
    uuid.reserve(length);

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
        Serial.print(output);
    }
    Serial.print("\n");

    if (on_rfid_received != nullptr)
    {
        on_rfid_received(uuid);
    }

    _period_ms = 0;
}