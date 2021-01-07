#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

#include "ble-pos-client-status.h"

class PosAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    BLEUUID _service_uuid;
    BLEPosClientStatus& _status;

public:
    PosAdvertisedDeviceCallbacks(BLEUUID& service_uuid, BLEPosClientStatus& status) : _service_uuid(service_uuid), _status(status)
    {

    }

    void onResult(BLEAdvertisedDevice advertisedDevice) override;
};