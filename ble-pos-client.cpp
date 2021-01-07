#include "ble-pos-client.h"

void BLEPosClient::Begin(const uint16_t interval_ms, const uint16_t window_ms, const bool is_active_scan, const uint32_t duration, const bool is_continue)
{
    BLEDevice::init(_device_name);

    BLEScan* scan = BLEDevice::getScan();
    scan->setAdvertisedDeviceCallbacks(new PosAdvertisedDeviceCallbacks(_service_uuid, _status));
    scan->setInterval(interval_ms);
    scan->setWindow(window_ms);
    scan->setActiveScan(is_active_scan);
    scan->start(duration, is_continue);
}

void BLEPosClient::End()
{
    BLEDevice::deinit();
}

void BLEPosClient::Update()
{
    if (_status.GetDoConnect())
    {
        Connect();

        _status.SetDoConnect(false);
    }

    if (_status.GetIsConnected())
    {
        // Write
        return;
    }

    if (_status.GetDoScan())
    {
        BLEDevice::getScan()->start(re_scan_duration);
    }
}

const bool BLEPosClient::Connect()
{
    BLEClient* client = BLEDevice::createClient();
    // setClientCallbacks()
    client->connect(_status.GetAdvertisedDevice());

    // Service, Characteristic固有
    BLERemoteService* const service = client->getService(_service_uuid);

    ReadCharacteristic(client, service, _num_characteristic_uuid);
}

const bool BLEPosClient::ReadCharacteristic(BLEClient* const client, BLERemoteService* const service, BLEUUID uuid, notify_callback callback)
{
    if (service == nullptr)
    {
        client->disconnect();
        return false;
    }

    BLERemoteCharacteristic* characteristic = service->getCharacteristic(uuid);

    if (characteristic == nullptr)
    {
        client->disconnect();
        return false;
    }

    if (characteristic->canNotify())
    {
        // registerForNotify
        if (callback != nullptr)
        {
            characteristic->registerForNotify(callback);
        }
    }

    return true;
}