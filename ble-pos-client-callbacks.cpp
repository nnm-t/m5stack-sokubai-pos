#include "ble-pos-client-callbacks.h"

void BLEPosClientCallbacks::onConnect(BLEClient* pClient)
{

}

void BLEPosClientCallbacks::onDisconnect(BLEClient* pClient)
{
    if (_callback == nullptr)
    {
        return;
    }

    _callback();
}