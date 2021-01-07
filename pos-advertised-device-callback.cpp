#include "pos-advertised-device-callbacks.h"

void PosAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(_service_uuid))
    {
        BLEDevice::getScan()->stop();

        _status.SetAdvertisedDevice(new BLEAdvertisedDevice(advertisedDevice));
        _status.SetDoConnect(true);
        _status.SetDoScan(true);
    }
}