#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

#include "i-serial.h"
#include "ble-advertised-device-container.h"

class BLEPosAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    BLEUUID _service_uuid;
    BLEAdvertisedDeviceContainer& _advertised_device;
    ISerial* const _serial;

public:
    BLEPosAdvertisedDeviceCallbacks(BLEUUID& service_uuid, BLEAdvertisedDeviceContainer& advertised_device, ISerial* const serial) : _service_uuid(service_uuid), _advertised_device(advertised_device), _serial(serial)
    {

    }

    void onResult(BLEAdvertisedDevice advertisedDevice) override;
};