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
	static std::string removeDuplicateSlashes( std::string &str)
	{
		std::string result;
		bool previouslySlashFound = false;

		for( uint i = 0; i < str.length(); i++ )
		{
			if( str[i] ==  '/' )
			{
				if( previouslySlashFound )
					continue;
				previouslySlashFound = true;
			}
			else
				previouslySlashFound = false;

			result.push_back( str[i]);
		}

		if( result[result.length()-1]  ==  '/')
			result.pop_back();

		return result;
	}

	static UriPathArray splitUriPath( std::string &str)
	{
		UriPathArray result;
		std::string pathElement = "";

		for( uint i = 1; i < str.length(); i++ )
		{
			if( str[i] ==  '/' )
			{
				result.push_back( pathElement);
				pathElement.clear();
				continue;
			}

			pathElement.push_back( str[i]);
		}

		if( !pathElement.empty())
			result.push_back( pathElement);

		return result;
	}
};

} /* namespace resm */
#endif /* SRC_URIHELPER_H_ */
