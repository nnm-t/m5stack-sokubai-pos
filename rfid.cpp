#include "rfid.h"

void RFID::Begin()
{
    Wire.begin();

    _mfrc522.PCD_Init();
}

void RFID::Update()
{
    if(!_mfrc522.PICC_IsNewCardPresent())
    {
        return;
    }

    if (!_mfrc522.PICC_ReadCardSerial())
    {
        return;
    }

    for (uint8_t i = 0; i < _mfrc522.uid.size; i++)
    {
        Serial.print(_mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(_mfrc522.uid.uidByte[i], HEX);
    }
}