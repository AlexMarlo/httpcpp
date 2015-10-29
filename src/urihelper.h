#ifndef SRC_URIHELPER_H_
#define SRC_URIHELPER_H_

#include <string>
#include <vector>

namespace resm
{
typedef std::vector< std::string> UriPathArray;

class UriHelper
{
public:
	static std::string removeDuplicateSlashes( std::string &str);
	static UriPathArray splitUriPath( std::string &str);
};

} /* namespace resm */
#endif /* SRC_URIHELPER_H_ */
