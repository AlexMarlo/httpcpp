#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H

#include "resourcemanagertypedefs.h"
#include <mutex>
#include <cstdint>

namespace resm
{

class ResourceManager
{
public:

	ResourceManager( uint32_t resourceCount);
	virtual ~ResourceManager();

	ResourceAllocateResult allocate( std::string user);
	bool deallocate( std::string resource);
	FullListResult list();
	ResourceListResult list( std::string user);
	void reset();

	int getResourceCount() const { return _resourceCount;}

private:
	void initResources();

private:
	typedef std::map<ResourceId, std::string> AllocatedInvert;

	uint32_t _resourceCount;
	std::mutex _mutex;

	Allocated _allocated;
	AllocatedInvert _allocatedInvert;
	Deallocated _deallocated;
};
} /* namespace resm */
#endif /* RESOURCEMANAGER_H_ */
