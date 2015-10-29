#include "httprequesthandler.h"
#include "jsonconverter.h"
#include "urihelper.h"

namespace http
{

HttpRequestHandler::HttpRequestHandler( uint32_t &resourceCount): resourceManager( resourceCount)
{}

HttpRequestHandler::~HttpRequestHandler()
{}

Response HttpRequestHandler::handle( Request &request)
{
	Response response = this->createBadRequestResponse();

	if( request.isGet())
	{
		std::string uri = request.getUri();
		resm::UriPathArray uriPathArray = resm::UriHelper::splitUriPath( uri);

		if( uriPathArray.size() == 2 && uriPathArray[0].compare( "deallocate") == 0)
		{
			response = this->createDeallocateResponse( uriPathArray[1]);
			return response;
		}

		if( uriPathArray.size() == 2 && uriPathArray[0].compare( "allocate") == 0)
		{
			response = this->createAllocateResponse( uriPathArray[1]);
			return response;
		}

		if( uriPathArray.size() == 2 && uriPathArray[0].compare( "list") == 0)
		{
			response = this->createUserListResponse( uriPathArray[1]);
			return response;
		}

		if( uri.compare( "/reset") == 0)
		{
			response = this->createResetResponse();
			return response;
		}

		if( uri.compare( "/list") == 0)
		{
			response = this->createListResponse();
			return response;
		}
	}

	return response;
}

Response HttpRequestHandler::createResetResponse()
{
	resourceManager.reset();
	Response response( 204, "No Content", "");
	return response;
}

Response HttpRequestHandler::createListResponse()
{
	resm::FullListResult fullListResult = resourceManager.list();
	std::string jsonList = resm::JsonConverter::listResultToJson( fullListResult);
	Response response( 200, "OK", jsonList);
	return response;
}

Response HttpRequestHandler::createBadRequestResponse()
{
	Response response( 400, "Bad Request", "Bad request.");
	return response;
}

Response HttpRequestHandler::createDeallocateResponse( std::string &resId)
{
	Response response( 404, "Not Found", "Not allocated.");
	if( resourceManager.deallocate( resId))
		response = Response( 204, "No Content", "");

	return response;
}

Response HttpRequestHandler::createAllocateResponse( std::string &user)
{
	Response response( 503, "Service Unavailable", "Out of resources.");
	resm::ResourceAllocateResult resourceAllocateResult = resourceManager.allocate( user);

	if( resourceAllocateResult.first)
		response = Response( 201, "Created", resourceAllocateResult.second);

	return response;
}

Response HttpRequestHandler::createUserListResponse( std::string &user)
{
	resm::ResourceListResult resourceListResult = resourceManager.list( user);
	std::string jsonList = resm::JsonConverter::resourcesListResultToJson( resourceListResult);
	Response response( 200, "OK", jsonList);
	return response;
}

} /* namespace http */
