#include "ble-pos-advertised-device-callbacks.h"

void BLEPosAdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    if (advertisedDevice.haveServiceUUID())
    {
        if (advertisedDevice.isAdvertisingService(_service_uuid))
        {
            BLEDevice::getScan()->stop();

            String address(advertisedDevice.getAddress().toString().c_str());

            _serial->Print("MAC: ");
            _serial->Println(address);
            _serial->Print("Service UUID: ");
            _serial->Println(advertisedDevice.getServiceUUID().toString().c_str());

            _advertised_device.SetAddress(address);
            _advertised_device.SetValue(new BLEAdvertisedDevice(advertisedDevice));
        }
    }
}