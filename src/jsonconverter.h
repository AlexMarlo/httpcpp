#ifndef SRC_JSONCONVERTER_H_
#define SRC_JSONCONVERTER_H_

#include "resourcemanagertypedefs.h"

namespace resm
{
class JsonConverter
{
public:
	static std::string listResultToJson( resm::FullListResult &fullListResult);
	static std::string resourcesListResultToJson( resm::ResourceListResult &resourceListResult);
};

} /* namespace resm */
#endif /* SRC_JSONCONVERTER_H_ */
