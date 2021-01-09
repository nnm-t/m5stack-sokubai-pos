#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

#include "ble-pos-advertised-device-callbacks.h"

class BLEPosClient
{
    static constexpr const uint32_t re_scan_duration = 0;

    const char* _device_name;
    BLEUUID _service_uuid;
    BLEUUID _num_characteristic_uuid;
    BLEUUID _price_characteristic_uuid;

    bool _is_connected = false;
    BLERemoteService* _service = nullptr;
    BLERemoteCharacteristic* _num_characteristic = nullptr;
    BLERemoteCharacteristic* _price_characteristic = nullptr;

    const bool ReadCharacteristic(BLEClient* const client, BLERemoteCharacteristic* const characteristic, notify_callback callback);

public:
    BLEPosClient(const char* device_name, BLEUUID& service_uuid, BLEUUID& num_characteristic_uuid, BLEUUID& price_characteristic_uuid) : _device_name(device_name), _service_uuid(service_uuid), _num_characteristic_uuid(num_characteristic_uuid), _price_characteristic_uuid(price_characteristic_uuid)
    {

    }

    void Begin(const uint16_t interval_ms = 1349, const uint16_t window_ms = 449, const bool is_active_scan = true, const uint32_t duration = 5, const bool is_continue = false);

    const bool Connect(BLEAdvertisedDevice* const advertised_device, notify_callback num_callback = nullptr, notify_callback price_callback = nullptr);

    void Update();

    void WriteNumber(const uint8_t number);

    void WritePrice(const uint16_t price);

    void End();
};