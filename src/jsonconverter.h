#ifndef SRC_JSONCONVERTER_H_
#define SRC_JSONCONVERTER_H_

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/writer.h>
#include <fstream>
#include <iostream>
#include "resourcemanagertypedefs.h"

namespace resm
{
class JsonConverter
{
public:
	static std::string listResultToJson( resm::FullListResult fullListResult)
	{
		Json::Value root;
		root[ "deallocated"].append(Json::Value::null);
		root[ "deallocated"].clear();

		bool hasAllocated = false;
		resm::Allocated::const_iterator itAlloc = fullListResult.first.begin();
		for( ; itAlloc != fullListResult.first.end(); ++itAlloc)
		{
			hasAllocated = true;
			root[ "allocated"][itAlloc->second] = itAlloc->first;
		}
		if( !hasAllocated)
		{
			root[ "allocated"].append( Json::Value::null);
			root[ "allocated"].clear();
		}

		resm::Deallocated::const_iterator itDealloc = fullListResult.second.begin();
		for( ; itDealloc != fullListResult.second.end(); ++itDealloc)
			root[ "deallocated"].append( *itDealloc);

		Json::FastWriter writer;
		std::string result = writer.write( root );

		if( !result.empty() && result[ result.length()-1] == '\n')
			result.pop_back();

		return result;
	}

	static std::string resourcesListResultToJson( resm::ResourceListResult resourceListResult)
	{
		Json::Value root;
		root.append(Json::Value::null);
		root.clear();

		resm::ResourceListResult::const_iterator it = resourceListResult.begin();
		for( ; it != resourceListResult.end(); ++it)
			root.append( *it);

		Json::FastWriter writer;
		std::string result = writer.write( root );

		if( !result.empty() && result[ result.length()-1] == '\n')
			result.pop_back();

		return result;
	}
};

} /* namespace resm */
#endif /* SRC_JSONCONVERTER_H_ */
