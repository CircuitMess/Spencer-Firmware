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

	/**
	 * Checks if a working Internet connection is established. First, by checking if the WiFi is connected,
	 * and then trying to establish a connection to spencer.circuitmess.com. This is a blocking function.
	 * @return True is all OK, false otherwise
	 */
	bool checkConnection();

	/**
	 * Reconnects the WiFi in a blocking fashion. 2 tries, 5s timeout
	 * @return True if succeeded, false otherwise
	 */
	bool reconnect();

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
