#ifndef TEST_CONFIGTEST_H_
#define TEST_CONFIGTEST_H_

#include <gtest/gtest.h>

#include <config.h>

namespace test
{

class ConfigTest  : public testing::Test {};

TEST_F( ConfigTest, ShouldParseConfig)
{
	std::string ip =resm::Config::readIp();
	EXPECT_EQ( "127.0.0.1", ip);
}

} /* namespace test */

#endif /* TEST_CONFIGTEST_H_ */
