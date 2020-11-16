#ifndef SPENCER_NET_H
#define SPENCER_NET_H

#include <WiFi.h>
#include <Loop/LoopListener.h>

class NetImpl : public LoopListener {
public:
	NetImpl();
	void set(const char* ssid, const char* pass);
	void connect();

	void loop(uint micros) override;

	void setStatusCallback(void (* statusCallback)(wl_status_t));

private:
	const char* ssid;
	const char* pass;

	void (* statusCallback)(wl_status_t) = nullptr;

	void tryConnect();
	void retryConnect();
	bool connecting = false;
	uint connectTime;
	uint8_t connectRetries;

};

extern NetImpl Net;

#endif //SPENCER_NET_H
