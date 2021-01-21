#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

class BLEAdvertisedDeviceContainer
{
    BLEAdvertisedDevice* _value = nullptr;
    String _address;

public:
    BLEAdvertisedDeviceContainer() : _address(String())
    {

    }

    void SetValue(BLEAdvertisedDevice* const value)
    {
        _value = value;
    }

    BLEAdvertisedDevice* GetValue()
    {
        return _value;
    }

    const bool IsAdvertised()
    {
        return _value != nullptr;
    }

    String GetAddress()
    {
        return _address;
    }

    void SetAddress(String& address)
    {
        _address = address;
    }

    void SetAddress(String address)
    {
        _address = address;
    }
};