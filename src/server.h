#ifndef SERVER_H_
#define SERVER_H_

#include <evhttp.h>
#include <cstdint>
#include "httprequesthandler.h"

namespace http
{

class Server
{
public:
	Server( HttpRequestHandler &httpRequestHandler);
	~Server();
	bool run( const std::string ip, const std::uint32_t port);

private:
	static void requestHandler( struct evhttp_request *request, void *serverPtr);

	HttpRequestHandler &_httpRequestHandler;
};

} /* namespace http */
#endif /* SERVER_H_ */
