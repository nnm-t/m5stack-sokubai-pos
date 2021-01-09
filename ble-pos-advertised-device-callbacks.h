#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

class BLEPosAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    BLEUUID _service_uuid;

public:
    BLEPosAdvertisedDeviceCallbacks(BLEUUID& service_uuid) : _service_uuid(service_uuid)
    {

    }

    void onResult(BLEAdvertisedDevice advertisedDevice) override;
};