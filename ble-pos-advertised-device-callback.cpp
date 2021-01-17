#include "ble-pos-advertised-device-callbacks.h"

void BLEPosAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    if (advertisedDevice.haveServiceUUID())
    {
        if (advertisedDevice.isAdvertisingService(_service_uuid))
        {
            BLEDevice::getScan()->stop();

            _advertised_device.SetValue(new BLEAdvertisedDevice(advertisedDevice));
        }
    }
}