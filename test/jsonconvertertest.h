#ifndef TEST_JSONCONVERTERTEST_H_
#define TEST_JSONCONVERTERTEST_H_

#include <gtest/gtest.h>

#include <jsonconverter.h>

namespace test
{

class JsonConverterTest  : public testing::Test {};

TEST_F( JsonConverterTest, ShouldConvertListToJsonWithEmptyAllocated)
{
	uint32_t resourceCount = 3;
	std::string expectedJson = "{\"allocated\":[],\"deallocated\":[\"r1\",\"r2\",\"r3\"]}";
	resm::ResourceManager resourceManager( resourceCount);

	resm::FullListResult fullListResult = resourceManager.list();
	std::string actualJson = resm::JsonConverter::listResultToJson( fullListResult);
	EXPECT_EQ( expectedJson, actualJson);
}

TEST_F( JsonConverterTest, ShouldConvertListToJsonWithEmptyDeallocated)
{
	uint32_t resourceCount = 3;
	std::string bob = "bob";
	std::string alice = "alice";
	std::string expectedJson = "{\"allocated\":{\"r1\":\"alice\",\"r2\":\"bob\",\"r3\":\"bob\"},\"deallocated\":[]}";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);

	resm::FullListResult fullListResult = resourceManager.list();
	std::string actualJson = resm::JsonConverter::listResultToJson( fullListResult);
	EXPECT_EQ( expectedJson, actualJson);
}

TEST_F( JsonConverterTest, ShouldConvertListToJson)
{
	uint32_t resourceCount = 3;
	std::string bob = "bob";
	std::string alice = "alice";
	std::string expectedJson = "{\"allocated\":{\"r1\":\"alice\",\"r2\":\"bob\"},\"deallocated\":[\"r3\"]}";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);

	resm::FullListResult fullListResult = resourceManager.list();
	std::string actualJson = resm::JsonConverter::listResultToJson( fullListResult);
	EXPECT_EQ( expectedJson, actualJson);
}

TEST_F( JsonConverterTest, ShouldConvertResourcesListToJson)
{
	uint32_t resourceCount = 3;
	std::string bob = "bob";
	std::string alice = "alice";
	std::string r2 = "r2";
	std::string expectedJson1 = "[\"r1\",\"r3\"]";
	std::string expectedJson2 = "[]";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_TRUE( resourceManager.deallocate( r2));

	resm::ResourceListResult resourceListResult = resourceManager.list( alice);
	std::string actualJson = resm::JsonConverter::resourcesListResultToJson( resourceListResult);
	EXPECT_EQ( expectedJson1, actualJson);

	resourceListResult = resourceManager.list( bob);
	actualJson = resm::JsonConverter::resourcesListResultToJson( resourceListResult);
	EXPECT_EQ( expectedJson2, actualJson);
}
} /* namespace test */
#endif /* TEST_JSONCONVERTERTEST_H_ */
