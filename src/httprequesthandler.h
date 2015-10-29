#ifndef SRC_HTTPREQUESTHANDLER_H_
#define SRC_HTTPREQUESTHANDLER_H_

#include "request.h"
#include "resourcemanager.h"
#include "response.h"

namespace http
{

class HttpRequestHandler
{
public:
	HttpRequestHandler( uint32_t &resourceCount);
	~HttpRequestHandler();

	Response handle( Request &request);

private:
	Response createResetResponse();
	Response createListResponse();
	Response createBadRequestResponse();
	Response createDeallocateResponse( std::string &resId);
	Response createAllocateResponse( std::string &user);
	Response createUserListResponse( std::string &user);

private:
	resm::ResourceManager resourceManager;
};

} /* namespace http */

#endif /* SRC_HTTPREQUESTHANDLER_H_ */
