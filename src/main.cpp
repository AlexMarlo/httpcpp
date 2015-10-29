#include <iostream>
#include <string>

#include "server.h"
#include "config.h"

int main()
{
	resm::Config config;
	std::string ip = config.readIp();
	std::uint32_t port = config.readPort();
	std::uint32_t resourceCount = config.readResourceCount();

	::http::HttpRequestHandler httpRequestHandler( resourceCount);
	::http::Server server( httpRequestHandler);
	if( !server.run( ip, port))
		std::cerr << "Failed to run server." << std::endl;
	return 0;
}
