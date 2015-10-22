#include <gtest/gtest.h>

#include "resourcemanagertest.h"
#include "jsonconvertertest.h"
//#include "configtest.h"


int main( int argc, char **argv)
{
	testing::InitGoogleTest( &argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}
