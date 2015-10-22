#include "response.h"

namespace http {

Response::Response( int status, std::string reason, std::string body):_status( status), _reason(reason), _body(body)
{}

Response::~Response()
{}

} /* namespace http */
