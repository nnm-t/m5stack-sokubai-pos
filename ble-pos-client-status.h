#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

class BLEPosClientStatus
{
    BLEAdvertisedDevice* _advertised_device = nullptr;

    bool _do_connect = false;
    bool _is_connected = false;
    bool _do_scan = false;

public:
    BLEPosClientStatus()
    {

    }

    const bool GetDoConnect()
    {
        return _do_connect;
    }

    const bool GetIsConnected()
    {
        return _is_connected;
    }

    const bool GetDoScan()
    {
        return _do_scan;
    }

    BLEAdvertisedDevice* const GetAdvertisedDevice()
    {
        return _advertised_device;
    }

    void SetDoConnect(const bool do_connect)
    {
        _do_connect = do_connect;
    }

    void SetDoScan(const bool do_scan)
    {
        _do_scan = do_scan;
    }

    void SetAdvertisedDevice(BLEAdvertisedDevice* const advertised_device)
    {
        _advertised_device = advertised_device;
    }
};