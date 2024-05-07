#pragma once

#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>

#include "i-serial.h"

class ESPNOW
{
	ISerial* const _serial;
	esp_now_peer_info_t _peer_info;

	bool _is_initialized = false;

	void AddPeer();

	void SendData(String& data);

public:
	ESPNOW(ISerial* const serial) : _serial(serial)
	{

	}

	void Begin();

	void Deserialize(JsonArray& mac_array);

	String GetPeerAddress();

	void SendGood(String& name, const int32_t price, const int32_t amount);

	void SendAmount(const int32_t amount);

	void SendComplete();
};