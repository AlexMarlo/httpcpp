#include "config.h"

namespace resm
{

Config::Config()
{
	Json::Reader reader;
	std::string configFile = CONFIG_PATH;//"config/config.json";
	std::ifstream config( configFile, std::ifstream::binary);
	std::string fileContent((std::istreambuf_iterator<char>(config)),
	                 	 	 std::istreambuf_iterator<char>());

	reader.parse( fileContent, root);
}

Config::~Config()
{}

std::string Config::readIp()
{
	std::string ip = root.get( "ip", "127.0.0.1" ).asString();
	return ip;
};

uint32_t Config::readPort()
{
	uint32_t port = root.get( "port", 5555 ).asUInt();
	return port;
};

uint32_t Config::readResourceCount()
{
	uint32_t resourceCount = root.get( "resourceCount", 3 ).asUInt();
	return resourceCount;
};

} /* namespace resm */
