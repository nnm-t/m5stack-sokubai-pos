#include "keyboard.h"

void Keyboard::Begin()
{
    pinMode(enable_pin, INPUT_PULLUP);

    Wire.begin();
}

void Keyboard::Update()
{
    if (digitalRead(enable_pin) != LOW)
    {
        return;
    }

    Wire.requestFrom(i2c_address, request_bytes);

    while(Wire.available())
    {
        uint8_t code = Wire.read();
        ReceiveKeyCode(code);
    }
}

void Keyboard::ReceiveKeyCode(const uint8_t code)
{

}