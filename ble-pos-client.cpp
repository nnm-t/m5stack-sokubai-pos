#include "ble-pos-client.h"

void BLEPosClient::Begin()
{
    BLEDevice::init(_device_name);
}

void BLEPosClient::Scan(const uint16_t interval_ms, const uint16_t window_ms, const bool is_active_scan, const uint32_t duration, const bool is_continue)
{
    BLEScan* scan = BLEDevice::getScan();
    scan->setAdvertisedDeviceCallbacks(new BLEPosAdvertisedDeviceCallbacks(_service_uuid, _advertised_device, _serial));
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
    if (_is_connected)
    {
        return;
    }

    if (!_advertised_device.IsAdvertised())
    {
        return;
    }

    // BLEDevice::getScan()->start(re_scan_duration);
}

void BLEPosClient::Write(const uint8_t number, const uint16_t price)
{
    if (_price_characteristic == nullptr || !_is_connected)
    {
        return;
    }

    std::array<uint8_t, 3> data = { number, price >> 8, price & 0xFF };
    _price_characteristic->writeValue(data.data(), data.size());
}

const bool BLEPosClient::Connect()
{
    if (_is_connected)
    {
        return false;
    }

    if (!_advertised_device.IsAdvertised())
    {
        return false;
    }

    // std::function<void()> disconnect_callback = [this]{ this->NotifyLostConnection(); };

    _client = BLEDevice::createClient();
    // _client->setClientCallbacks(new BLEPosClientCallbacks(disconnect_callback));
    if (!_client->connect(_advertised_device.GetValue()))
    {
        _serial->Println("BLE Connection Failed");
        return false;
    }

    _serial->Println("BLE Connected");
    _is_connected = true;

    _service = _client->getService(_service_uuid);

    if (_service == nullptr)
    {
        Disconnect();

        _serial->Println("BLE Service can't initialized");
        return false;
    }

    _serial->Println("BLE Service initialized");

    _price_characteristic = _service->getCharacteristic(_price_characteristic_uuid);

    if (_price_characteristic == nullptr)
    {
        Disconnect();
        _serial->Println("BLE Characteristic can't initialized");
        return false;
    }

    _serial->Println("BLE Ready");
    return true;
}

const bool BLEPosClient::ReadCharacteristic(BLEClient* const client, BLERemoteCharacteristic* const characteristic, notify_callback callback)
{
    if (characteristic == nullptr)
    {
        Disconnect();
        return false;
    }

    if (characteristic->canNotify())
    {
        if (callback != nullptr)
        {
            characteristic->registerForNotify(callback);
        }
    }

    return true;
}

const bool BLEPosClient::Disconnect()
{
    if (!_is_connected)
    {
        return false;
    }

    _client->disconnect();
    _is_connected = false;
    _serial->Println("BLE Disconnected");

    return true;
}