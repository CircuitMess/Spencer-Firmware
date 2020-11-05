#include <SerialFlash.h>
#include <map>
#include "SetupRequestHandler.h"

std::map<std::string, const char*> mimes = {
		{ std::string("html"), "text/html" },
		{ std::string("js"), "application/javascript" },
		{ std::string("css"), "text/css" },
		{ std::string("png"), "image/png" },
		{ std::string("ttf"), "font/ttf" }
};

bool SetupRequestHandler::handle(WebServer& server, HTTPMethod requestMethod, String requestUri){
	if(requestUri == "/"){
		requestUri = "/index.html";
	}

	String extesion = requestUri.substring(requestUri.lastIndexOf('.') + 1);
	auto mime = mimes.find(std::string(extesion.c_str()));
	if(mime == mimes.end()){
		server.send(404);
		return true;
	}

	String resource = requestUri.substring(1); // remove first slash
	resource.replace('/', '-'); // replace slashes with dashes (flat FS)
	String file = "www-" + resource + ".gz";

	if(!SerialFlash.exists(file.c_str())){
		server.send(404);
		return true;
	}

	server.sendHeader("Content-Encoding", "gzip");
	server.sendHeader("Content-Type", mime->second);

	sendFile(server, file.c_str());
	return true;
}

bool SetupRequestHandler::canHandle(HTTPMethod method, String uri){
	return method == HTTP_GET;
}

void SetupRequestHandler::sendFile(WebServer& server, const char* path){
	SerialFlashFile file = SerialFlash.open(path);
	if(!file){
		server.send(404);
		return;
	}

	server.setContentLength(file.size());
	server.send(200);

	char buffer[1024];
	uint readBytes;
	while(readBytes = file.read(buffer, 1024)){
		server.sendContent_P(buffer, readBytes);
	}
}