#include "esp-now.h"

void ESPNOW::Begin()
{
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();

	if (esp_now_init() != ESP_OK)
	{
		_serial->Println("ESP-NOW init failed");
		return;
	}

	_is_initialized = true;
	_serial->Println("ESP-NOW init success");
}

void ESPNOW::Deserialize(JsonArray& mac_array)
{
	memset(&_peer_info, 0, sizeof(_peer_info));

	_peer_info.channel = 0;
	_peer_info.encrypt = false;

	if (mac_array.size() != 6)
	{
		_peer_info.peer_addr[0] = 0x00;
		_peer_info.peer_addr[1] = 0x00;
		_peer_info.peer_addr[2] = 0x00;
		_peer_info.peer_addr[3] = 0x00;
		_peer_info.peer_addr[4] = 0x00;
		_peer_info.peer_addr[5] = 0x00;

		AddPeer();
		return;
	}

	_peer_info.peer_addr[0] = mac_array[0];
	_peer_info.peer_addr[1] = mac_array[1];
	_peer_info.peer_addr[2] = mac_array[2];
	_peer_info.peer_addr[3] = mac_array[3];
	_peer_info.peer_addr[4] = mac_array[4];
	_peer_info.peer_addr[5] = mac_array[5];

	AddPeer();
}

void ESPNOW::AddPeer()
{
	if (esp_now_add_peer(&_peer_info) != ESP_OK)
	{
		_serial->Println("ESP-NOW pairing failed");
		return;
	}

	_serial->Println("ESP-NOW pairing success");
}

String ESPNOW::GetPeerAddress()
{
	char str[18];
	snprintf(str, sizeof(str), "%02X:%02X:%02X:%02X:%02X:%02X", _peer_info.peer_addr[0], _peer_info.peer_addr[1], _peer_info.peer_addr[2], _peer_info.peer_addr[3], _peer_info.peer_addr[4], _peer_info.peer_addr[5]);

	return String(str);
}

void ESPNOW::SendData(String& data)
{
	if (data.length() > 250)
	{
		_serial->Println("ESP-NOW send data is too long");
		return;
	}

	_serial->Println(data);

	uint8_t send_data[256];

	send_data[0] = _peer_info.peer_addr[0];
	send_data[1] = _peer_info.peer_addr[1];
	send_data[2] = _peer_info.peer_addr[2];
	send_data[3] = _peer_info.peer_addr[3];
	send_data[4] = _peer_info.peer_addr[4];
	send_data[5] = _peer_info.peer_addr[5];

	memcpy(send_data + 6, data.c_str(), data.length());

	const esp_err_t result = esp_now_send(_peer_info.peer_addr, send_data, data.length() + 6);

	switch (result)
	{
		case ESP_OK:
			_serial->Println("ESP-NOW send success");
			break;
		case ESP_ERR_ESPNOW_NOT_INIT:
			_serial->Println("ESP-NOW not init");
			break;
		case ESP_ERR_ESPNOW_ARG:
			_serial->Println("ESP-NOW invalid argument");
			break;
		case ESP_ERR_ESPNOW_INTERNAL:
			_serial->Println("ESP-NOW internal error");
			break;
		case ESP_ERR_ESPNOW_NO_MEM:
			_serial->Println("ESP-NOW no memory");
			break;
		case ESP_ERR_ESPNOW_NOT_FOUND:
			_serial->Println("ESP-NOW peer not found");
			break;
		default:
			_serial->Println("ESP-NOW unknown error occured");
			break;
	}
}

void ESPNOW::SendGood(String& name, const int32_t price, const int32_t amount)
{
	StaticJsonDocument<256> json;
	json["name"] = name;
	json["price"] = price;
	json["sum"] = amount;

	String data;
	serializeJson(json, data);

	SendData(data);
}

void ESPNOW::SendAmount(const int32_t amount)
{
	StaticJsonDocument<256> json;
	json["price"] = amount;

	String data;
	serializeJson(json, data);

	SendData(data);
}

void ESPNOW::SendComplete()
{
	StaticJsonDocument<256> json;
	json["complete"] = true;

	String data;
	serializeJson(json, data);

	SendData(data);
}
