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
	Config();
	~Config();

	std::string readIp();
	uint32_t readPort();
	uint32_t readResourceCount();
private:
	Json::Value root;
};

} /* namespace resm */
#endif /* SRC_CONFIG_H_ */
