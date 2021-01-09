#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

class BLEAdvertisedDeviceContainer
{
    BLEAdvertisedDevice* _value = nullptr;

public:
    BLEAdvertisedDeviceContainer()
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
};