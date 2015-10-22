#ifndef SRC_REQUEST_H_
#define SRC_REQUEST_H_

#include <string>

namespace http
{

class Request
{

public:
	enum TYPE { GET, POST, PUT, DELETE, OTHER };

	Request( TYPE type, std::string uri);
	virtual ~Request();

	bool isGet()
	{
		return this->_type == GET;
	}

	const std::string& getUri() const
	{
		return _uri;
	}

private:
	TYPE _type;
	std::string _uri;
};

} /* namespace http */

#endif /* SRC_REQUEST_H_ */
