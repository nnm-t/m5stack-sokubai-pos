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
        if (_price_characteristic == nullptr)
        {
            return;
        }

        if (!_is_write_ready)
        {
            return;
        }

        _price_characteristic->writeValue(_write_data.data(), _write_data.size());

        String write_data_string = "BLE Send:";
        for (uint8_t i = 0; i < _write_data.size(); i++)
        {
            write_data_string += " ";
            write_data_string += String(_write_data[i]);
        }

        Serial.println(write_data_string);

        _is_write_ready = false;

        return;
    }

    if (!_advertised_device.IsAdvertised())
    {
        return;
    }

    // BLEDevice::getScan()->start(re_scan_duration);
}

void BLEPosClient::Write(const BLEPosDataType type, const uint8_t number, const uint32_t price)
{
    if (_price_characteristic == nullptr || !_is_connected)
    {
        return;
    }

    _write_data[0] = static_cast<uint8_t>(type);
    _write_data[1] = number;
    _write_data[2] = price >> 24;
    _write_data[3] = (price >> 16) & 0xFF;
    _write_data[4] = (price >> 8) & 0xFF;
    _write_data[5] = price & 0xFF;

    _is_write_ready = true;
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