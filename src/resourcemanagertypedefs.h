#ifndef SRC_RESOURCEMANAGERTYPEDEFS_H_
#define SRC_RESOURCEMANAGERTYPEDEFS_H_

#include <string>
#include <map>
#include <list>

namespace resm
{

typedef std::string ResourceId;
typedef std::pair< bool, ResourceId> ResourceAllocateResult;
typedef std::multimap<std::string, ResourceId> Allocated;
typedef std::list<ResourceId> Deallocated;
typedef std::pair< Allocated, Deallocated> FullListResult;
typedef std::list< ResourceId> ResourceListResult;

} /* namespace resm */
#endif /* SRC_RESOURCEMANAGERTYPEDEFS_H_ */
