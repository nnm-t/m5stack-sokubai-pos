#include "ble-pos-advertised-device-callbacks.h"

void BLEPosAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(_service_uuid))
    {
        BLEDevice::getScan()->stop();

        //new BLEAdvertisedDevice(advertisedDevice);
    }
}