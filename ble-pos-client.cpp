#include "ble-pos-client.h"

void BLEPosClient::Begin(const uint16_t interval_ms, const uint16_t window_ms, const bool is_active_scan, const uint32_t duration, const bool is_continue)
{
    BLEDevice::init(_device_name);

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

    if (_advertised_device.IsAdvertised())
    {
        Connect();
        return;
    }

    // BLEDevice::getScan()->start(re_scan_duration);
}

void BLEPosClient::WriteNumber(const uint8_t number)
{
    if (_num_characteristic == nullptr || !_is_connected)
    {
        return;
    }

    _num_characteristic->writeValue(number);
}

void BLEPosClient::WritePrice(const uint16_t price)
{
    if (_price_characteristic == nullptr || !_is_connected)
    {
        return;
    }

    std::array<uint8_t, 2> data = { price >> 8, price & 0xFF };
    _price_characteristic->writeValue(data.data(), data.size());
}

const bool BLEPosClient::Connect(notify_callback num_callback, notify_callback price_callback)
{
    if (_is_connected)
    {
        return false;
    }

    if (!_advertised_device.IsAdvertised())
    {
        return false;
    }

    BLEClient* client = BLEDevice::createClient();
    // setClientCallbacks()
    if (!client->connect(_advertised_device.GetValue()))
    {
        _serial->Println("BLE Connection Failed");
        return false;
    }

    _serial->Println("BLE Connected");
    _is_connected = true;

    _service = client->getService(_service_uuid);

    if (_service == nullptr)
    {
        client->disconnect();
        _is_connected = false;

        _serial->Println("BLE Service can't initialized");
        return false;
    }

    _serial->Println("BLE Service initialized");

    _serial->Println(_num_characteristic_uuid.toString().c_str());
    _serial->Println(_price_characteristic_uuid.toString().c_str());

    _num_characteristic = _service->getCharacteristic(_num_characteristic_uuid);
    _price_characteristic = _service->getCharacteristic(_price_characteristic_uuid);

    if (_num_characteristic == nullptr || _price_characteristic == nullptr)
    {
        client->disconnect();
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
        client->disconnect();
        _is_connected = false;
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