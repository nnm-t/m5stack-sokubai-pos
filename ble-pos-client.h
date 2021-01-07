#pragma once

#include "Arduino.h"
#include "M5Stack.h"
#include "BLEDevice.h"

#include "ble-pos-client-status.h"
#include "pos-advertised-device-callbacks.h"

class BLEPosClient
{
    static constexpr const uint32_t re_scan_duration = 0;

    const char* _device_name;
    BLEUUID _service_uuid;
    BLEUUID _num_characteristic_uuid;
    BLEUUID _price_characteristic_uuid;

    BLEPosClientStatus _status;

    const bool Connect();

    const bool ReadCharacteristic(BLEClient* const client, BLERemoteService* const service, BLEUUID uuid, notify_callback callback = nullptr);

public:
    BLEPosClient(const char* device_name, BLEUUID& service_uuid, BLEUUID& num_characteristic_uuid, BLEUUID& price_characteristic_uuid) : _device_name(device_name), _service_uuid(service_uuid), _num_characteristic_uuid(num_characteristic_uuid), _price_characteristic_uuid(price_characteristic_uuid), _status(BLEPosClientStatus())
    {

    }

    void Begin(const uint16_t interval_ms = 1349, const uint16_t window_ms = 449, const bool is_active_scan = true, const uint32_t duration = 5, const bool is_continue = false);

    void Update();

    void End();
};