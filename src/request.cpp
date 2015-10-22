#include "request.h"

namespace http {

Request::Request(  TYPE type, std::string uri): _type( type), _uri( uri)
{
}

Request::~Request()
{}

} /* namespace http */
