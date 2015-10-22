#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>
#include <fstream>

namespace resm
{

class Config
{
public:
	static std::string readIp()
	{
		Json::Value root = Config::readConfig();
		std::string ip = root.get( "ip", "127.0.0.1" ).asString();
		return ip;
	};

	static uint32_t readPort()
	{
		Json::Value root = Config::readConfig();
		uint32_t port = root.get( "port", 5555 ).asUInt();
		return port;
	};

	static uint32_t readResourceCount()
	{
		Json::Value root = Config::readConfig();
		uint32_t resourceCount = root.get( "resourceCount", 3 ).asUInt();
		return resourceCount;
	};
private:
	static Json::Value readConfig()
	{
		Json::Reader reader;
		std::string configFile = CONFIG_PATH;//"config/config.json";
		std::ifstream config( configFile, std::ifstream::binary);
		std::string fileContent((std::istreambuf_iterator<char>(config)),
		                 	 	 std::istreambuf_iterator<char>());

		Json::Value root;
		reader.parse( fileContent, root);

		return root;
	}
};

} /* namespace resm */
#endif /* SRC_CONFIG_H_ */
