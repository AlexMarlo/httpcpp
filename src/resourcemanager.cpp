#include "resourcemanager.h"

namespace resm
{

ResourceManager::ResourceManager( uint32_t &resourceCount):  _resourceCount( resourceCount)
{
	initResources();
}

ResourceManager::~ResourceManager()
{}

ResourceAllocateResult ResourceManager::allocate( std::string &user)
{
	Deallocated::iterator it = _deallocated.begin();

	if( it == _deallocated.end())
		return ResourceAllocateResult( false, "");

	ResourceId resId = (*it);
	_deallocated.pop_front();
	_allocated.insert( std::make_pair( user, resId));
	_allocatedInvert.insert( std::make_pair( resId, user));
	return ResourceAllocateResult( true, resId);
}

bool ResourceManager::deallocate( std::string &resource)
{
	AllocatedInvert::iterator itUser = _allocatedInvert.find( resource);
	if( itUser == _allocatedInvert.end())
		return false;

    std::pair <Allocated::iterator, Allocated::iterator> range;
    range = _allocated.equal_range( itUser->second);

    for( Allocated::iterator itRes = range.first; itRes != range.second; ++itRes)
    {
    	if( itRes->second.compare( resource) == 0)
    	{
			_deallocated.push_back( resource);
			_deallocated.sort();
			_allocated.erase( itRes);
			_allocatedInvert.erase( itUser);
			return true;
    	}
    }

	return false;
}

void ResourceManager::reset()
{
	_deallocated.clear();
	_allocated.clear();
	_allocatedInvert.clear();
	initResources();
}

FullListResult ResourceManager::list()
{
	FullListResult fullListResult( _allocated, _deallocated);
	return fullListResult;
}

ResourceListResult ResourceManager::list( std::string &user)
{
	ResourceListResult resourceListResult;
    std::pair <Allocated::const_iterator, Allocated::const_iterator> range = _allocated.equal_range( user);

    for( Allocated::const_iterator itRes = range.first; itRes != range.second; ++itRes)
    	resourceListResult.push_back( itRes->second);

	return resourceListResult;
}

void ResourceManager::initResources()
{
	std::string resId;
	for( uint16_t i = 1 ; i<=_resourceCount; i++)
	{
		resId = "r"+std::to_string( i);
		_deallocated.push_back( resId);
	}
}

} /* namespace resm */
