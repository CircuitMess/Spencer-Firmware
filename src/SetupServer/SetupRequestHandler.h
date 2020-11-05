#ifndef SPENCER_SETUPREQUESTHANDLER_H
#define SPENCER_SETUPREQUESTHANDLER_H


#include <WebServer.h>
#include <detail/RequestHandler.h>

class SetupRequestHandler : public RequestHandler {
public:
	bool handle(WebServer& server, HTTPMethod requestMethod, String requestUri) override;
	bool canHandle(HTTPMethod method, String uri) override;

private:
	void sendFile(WebServer& server, const char* path);

};


#endif //SPENCER_SETUPREQUESTHANDLER_H
