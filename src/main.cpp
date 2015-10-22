#include <iostream>
#include <string>

#include "server.h"
#include "config.h"

int main()
{
	std::string ip = resm::Config::readIp();
	std::uint32_t port = resm::Config::readPort();
	std::uint32_t resourceCount = resm::Config::readResourceCount();

	::http::HttpRequestHandler httpRequestHandler( resourceCount);
	::http::Server server( httpRequestHandler);
	if( !server.run( ip, port))
		std::cerr << "Failed to run server." << std::endl;
	return 0;
}
