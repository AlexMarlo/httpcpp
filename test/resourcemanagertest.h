#ifndef RESOURCEMANAGERTEST_H_
#define RESOURCEMANAGERTEST_H_

#include <gtest/gtest.h>

#include <resourcemanager.h>

namespace test
{

class ResourceManagerTest  : public testing::Test {};

TEST_F( ResourceManagerTest, ShouldReturnCorrectResourceCount)
{
	uint16_t resourceCount = 10;
	resm::ResourceManager resourceManager( resourceCount);

	EXPECT_EQ( resourceCount, resourceManager.getResourceCount());
}

TEST_F( ResourceManagerTest, ShouldAllocateRes)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	std::string r1 = "r1";
	resm::ResourceManager resourceManager( resourceCount);

	resm::ResourceAllocateResult result = resourceManager.allocate( bob);
	ASSERT_TRUE( result.first);
	EXPECT_EQ( r1, result.second);
}

TEST_F( ResourceManagerTest, ShouldNotAllocateIfOutOfResources)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_FALSE( resourceManager.allocate( bob).first);
}

TEST_F( ResourceManagerTest, ShouldDeallocate)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	std::string r1 = "r1";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.deallocate( r1));

	resm::ResourceAllocateResult result = resourceManager.allocate( bob);
	ASSERT_TRUE( result.first);
	EXPECT_EQ( r1, result.second);
}

TEST_F( ResourceManagerTest, ShouldNotDeallocateUndefinedRes)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	std::string r1 = "any";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_FALSE( resourceManager.deallocate( r1));
}

TEST_F( ResourceManagerTest, ShouldNotDeallocateAlredyDeallocatedRes)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	std::string r1 = "r1";
	std::string r2 = "r2";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.deallocate( r1));
	ASSERT_FALSE( resourceManager.deallocate( r1));
	ASSERT_TRUE( resourceManager.deallocate( r2));
}

TEST_F( ResourceManagerTest, ShouldReset)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	std::string alice = "alice";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( alice).first);

	resourceManager.reset();

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( alice).first);
}

TEST_F( ResourceManagerTest, ShouldAllocateFirstAvailable)
{
	uint16_t resourceCount = 4;
	std::string bob = "bob";
	std::string alice = "alice";
	std::string r3 = "r3";
	std::string r2 = "r2";
	resm::ResourceManager resourceManager( resourceCount);

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_FALSE( resourceManager.allocate( bob).first);

	ASSERT_TRUE( resourceManager.deallocate( r2));
	ASSERT_TRUE( resourceManager.deallocate( r3));

	resm::ResourceAllocateResult result = resourceManager.allocate( alice);
	ASSERT_TRUE( result.first);
	EXPECT_EQ( r2, result.second);
}

TEST_F( ResourceManagerTest, ShouldFullList)
{
	uint16_t resourceCount = 2;
	std::string bob = "bob";
	std::string alice = "alice";
	std::string r1 = "r1";
	resm::ResourceManager resourceManager( resourceCount);

	resm::FullListResult fullListResult = resourceManager.list();
	EXPECT_EQ( 0, fullListResult.first.size());
	EXPECT_EQ( 2, fullListResult.second.size());

	ASSERT_TRUE( resourceManager.allocate( bob).first);

	fullListResult = resourceManager.list();
	EXPECT_EQ( 1, fullListResult.first.size());
	EXPECT_EQ( 1, fullListResult.second.size());

	resm::Allocated::iterator it = fullListResult.first.find( bob);
	EXPECT_NE( it, fullListResult.first.end());
	EXPECT_EQ( it->first, bob);
	EXPECT_EQ( it->second, r1);

	ASSERT_TRUE( resourceManager.allocate( alice).first);

	fullListResult = resourceManager.list();
	EXPECT_EQ( 2, fullListResult.first.size());
	EXPECT_EQ( 0, fullListResult.second.size());
}

TEST_F( ResourceManagerTest, ShouldListForUser)
{
	uint16_t resourceCount = 4;
	std::string bob = "bob";
	std::string alice = "alice";
	std::string r1 = "r1";
	std::string r2 = "r2";
	std::string r3 = "r3";
	std::string r4 = "r4";
	resm::ResourceManager resourceManager( resourceCount);

	resm::ResourceListResult resourceListResult = resourceManager.list( alice);
	EXPECT_EQ( 0, resourceListResult.size());

	ASSERT_TRUE( resourceManager.allocate( bob).first);
	ASSERT_TRUE( resourceManager.allocate( alice).first);

	resourceListResult = resourceManager.list( alice);
	EXPECT_EQ( 1, resourceListResult.size());
	EXPECT_EQ( r2, (*resourceListResult.begin()));

	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_TRUE( resourceManager.allocate( alice).first);
	ASSERT_FALSE( resourceManager.allocate( alice).first);

	resourceListResult = resourceManager.list( alice);
	EXPECT_EQ( 3, resourceListResult.size());
	EXPECT_EQ( r2, (*resourceListResult.begin()));
	EXPECT_EQ( r3, (*(++resourceListResult.begin())));
	EXPECT_EQ( r4, (*resourceListResult.rbegin()));

	ASSERT_TRUE( resourceManager.deallocate( r3));

	resourceListResult = resourceManager.list( alice);
	EXPECT_EQ( 2, resourceListResult.size());
	EXPECT_EQ( r2, (*resourceListResult.begin()));
	EXPECT_EQ( r4, (*resourceListResult.rbegin()));
}
} /* namespace test */
#endif /* RESOURCEMANAGERTEST_H_ */
