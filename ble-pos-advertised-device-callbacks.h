#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

#include "ble-advertised-device-container.h"

class BLEPosAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    BLEUUID _service_uuid;
    BLEAdvertisedDeviceContainer& _advertised_device;

public:
    BLEPosAdvertisedDeviceCallbacks(BLEUUID& service_uuid, BLEAdvertisedDeviceContainer& advertised_device) : _service_uuid(service_uuid), _advertised_device(advertised_device)
    {

    }

    void onResult(BLEAdvertisedDevice advertisedDevice) override;
};