#include "server.h"

#include <memory>
#include <evhttp.h>
#include <iostream>

#include "request.h"
#include "urihelper.h"

namespace http
{

Server::Server( HttpRequestHandler &httpRequestHandler):  _httpRequestHandler( httpRequestHandler)
{}

Server::~Server()
{}

bool Server::run( const std::string ip, const std::uint32_t port)
{
	if (!event_init())
		return false;

	std::unique_ptr< evhttp, decltype(&evhttp_free)> resmServer( evhttp_start( ip.c_str(), port), &evhttp_free);
	if (!resmServer)
		return false;

	std::cout << "Server run "<< ip << ":" << port << std::endl;

	evhttp_set_gencb( resmServer.get(), Server::requestHandler, (void*)this);
	if (event_dispatch() == -1)
		return false;

	return true;
}

void Server::requestHandler( evhttp_request* evRequest, void* serverPtr)
{
	Server* server = (Server*)serverPtr;

	Request::TYPE type = Request::GET;
	if( evRequest->type != evhttp_cmd_type::EVHTTP_REQ_GET)
	  type = Request::OTHER;

	std::string uri = resm::UriHelper::removeDuplicateSlashes( evRequest->uri);
	Request request( type, uri);
	Response response = server->_httpRequestHandler.handle( request);

	evhttp_add_header( evRequest->output_headers, "Content-Type", "application/javascript; charset=utf-8");
//	evhttp_add_header( request->output_headers, "Content-Type", "application/json; charset=utf-8");
	auto *evResponse = evhttp_request_get_output_buffer( evRequest);
	if (!evResponse)
		return;

	evbuffer_add_printf( evResponse, "%s", response.getBody().c_str());
	evhttp_send_reply( evRequest, response.getStatus(), response.getReason().c_str(), evResponse);
}
} /* namespace http */

