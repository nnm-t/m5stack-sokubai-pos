#pragma once

#include <array>
#include <functional>

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

#include "i-serial.h"
#include "ble-pos-advertised-device-callbacks.h"
#include "ble-advertised-device-container.h"
#include "ble-pos-client-callbacks.h"
#include "ble-pos-data-type.h"

class BLEPosClient
{
    static constexpr const uint32_t re_scan_duration = 0;

    const char* _device_name;
    BLEUUID _service_uuid;
    BLEUUID _num_characteristic_uuid;
    BLEUUID _price_characteristic_uuid;
    ISerial* const _serial;

    BLEAdvertisedDeviceContainer _advertised_device;

    bool _is_connected = false;
    BLEClient* _client = nullptr;
    BLERemoteService* _service = nullptr;
    BLERemoteCharacteristic* _price_characteristic = nullptr;

public:
    BLEPosClient(const char* device_name, BLEUUID& service_uuid, BLEUUID& num_characteristic_uuid, BLEUUID& price_characteristic_uuid, ISerial* const serial) : _device_name(device_name), _service_uuid(service_uuid), _num_characteristic_uuid(num_characteristic_uuid), _price_characteristic_uuid(price_characteristic_uuid), _advertised_device(BLEAdvertisedDeviceContainer()), _serial(serial)
    {

    }

    void Begin();

    void Scan(const uint16_t interval_ms = 1349, const uint16_t window_ms = 449, const bool is_active_scan = true, const uint32_t duration = 5, const bool is_continue = false);

    const bool Connect();

    const bool Disconnect();

    void NotifyLostConnection()
    {
        _is_connected = false;
    }

    const bool IsConnected()
    {
        return _is_connected;
    }

    const bool IsAdvertised()
    {
        return _advertised_device.IsAdvertised();
    }

    String GetAdvertisedDeviceAddress()
    {
        return _advertised_device.GetAddress();
    }

    const bool ReadCharacteristic(BLEClient* const client, BLERemoteCharacteristic* const characteristic, notify_callback callback);

    void Update();

    void Write(const BLEPosDataType type, const uint8_t number, const uint32_t price);
    
    void Write(const BLEPosDataType type, const uint32_t price)
    {
        Write(type, 0x00, price);
    }
    
    void Write(const BLEPosDataType type)
    {
        Write(type, 0x00, 0x00);
    }

    void End();
};