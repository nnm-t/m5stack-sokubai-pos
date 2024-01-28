#pragma once

#include <functional>

#include <Arduino.h>
#include <M5Stack.h>
#include <BLEDevice.h>

class BLEPosClientCallbacks : public BLEClientCallbacks
{
    std::function<void()> _callback;

public:
    BLEPosClientCallbacks(std::function<void()> callback) : _callback(callback)
    {

    }

    void onConnect(BLEClient* pClient) override;

    void onDisconnect(BLEClient* pClient) override;
};