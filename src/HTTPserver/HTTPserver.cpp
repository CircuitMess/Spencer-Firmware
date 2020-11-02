#include "HTTPserver.h"
#include <WiFi.h>
#include <loop/LoopManager.h>
HTTPserver* HTTPserver::instance = nullptr;
const char* HTTPserver::index_html = nullptr;

const byte DNS_PORT = 53;
IPAddress apIP(8,8,4,4); // The default android DNS
DNSServer dnsServer;
HTTPserver::HTTPserver(/* args */)
{
	instance = this;
	IPAddress local_ip(192,168,1,1);
	IPAddress gateway(192,168,1,1);
	IPAddress subnet(255,255,255,0);
	WebServer server(80);

	index_html PROGMEM = R"rawliteral(
	<!DOCTYPE HTML><html><head>
	<title>ESP Input Form</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	</head><body>
	<p>Input your wifi creditentials here:</p>
	<form action="/savesettings">
		SSID: <input type="text" name="SSID"><br>
		<br>
		password: <input type="text" name="PASS"><br>
		<br>
		apikey1: <input type="text" name="apikey1"><br>
		<br>
		apikey2: <input type="text" name="apikey2"><br>
		<br>
		<input type="submit" value="Submit">
	</form><br>
	</body></html>)rawliteral";
}

HTTPserver::~HTTPserver()
{
}

void HTTPserver::start()
{
	Serial.println("Configuring access point...");
	// WiFi.mode(WIFI_AP_STA);
	WiFi.softAP(host_ssid, "");
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

	// if DNSServer is started with "*" for domain name, it will reply with
	// provided IP to all DNS request
	dnsServer.start(DNS_PORT, "*", apIP);
	// WiFi.softAPConfig(local_ip, gateway, subnet);
	delay(1000);
	Serial.println(WiFi.softAPIP());

	// Send web page with input fields to client
	server.on("/", HTTP_GET, [](){
		instance->server.send(200, "text/html", index_html);

	});
	server.onNotFound([](){
		instance->server.send(404, "text/plain", "Not found");
	});
	// Send a GET request to <ESP_IP>/get?input1=<inputMessage>
	server.on("/get", HTTP_GET, [](){
		char connect_ssid[64];
		char connect_pass[64];
		// GET input1 value on <ESP_IP>/get?input1=<inputMessage>
		
	});
	server.on("/listwifi", HTTP_GET, [](){
		String output = "";
		int n = WiFi.scanNetworks();
		Serial.println("scan done");
		if (n == 0) {
			output = "no networks found";
		} else {
			Serial.print(n);
			output = "networks: \n";
			Serial.println(" networks found");
			for (int i = 0; i < n; ++i) {
				// Print SSID and RSSI for each network found
				output+=WiFi.SSID(i) + "\n";
				// Serial.print();
				// Serial.print(" (");
				// Serial.print(WiFi.RSSI(i));
				// Serial.print(")");
				// Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
				// delay(10);
			}
		}
		instance->server.send(200, "text/html", output);
	});
	server.on("/savesettings", HTTP_GET, [](){
		char apikey1[40];
		char apikey2[40];
		char connect_ssid[64];
		char connect_pass[64];
		instance->server.arg(0).toCharArray(connect_ssid, 64);
		instance->server.arg(1).toCharArray(connect_pass, 64);
		instance->server.arg(2).toCharArray(apikey1, 40);
		instance->server.arg(3).toCharArray(apikey2, 40);
		instance->server.send(200, "text/html", "Connecting to network " + String(connect_ssid) +
			" with password " + String(connect_pass) + ". Key1: " + String(apikey1) + ", key2: " + String(apikey2));
	});
	server.begin();
	Serial.println("Server started");
	LoopManager::addListener(this);
}

void HTTPserver::loop(uint _time)
{
	dnsServer.processNextRequest();
	server.handleClient();
}