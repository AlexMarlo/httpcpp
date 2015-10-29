#ifndef SRC_RESPONSE_H_
#define SRC_RESPONSE_H_

#include <string>

namespace http
{

class Response
{
public:
	Response( int status, std::string reason, std::string body);
	~Response();

	const std::string& getBody() const
	{
		return _body;
	}

	int getStatus() const
	{
		return _status;
	}

	const std::string& getReason() const
	{
		return _reason;
	}

private:
	int _status;
	std::string _reason;
	std::string _body;
};

} /* namespace http */

#endif /* SRC_RESPONSE_H_ */
