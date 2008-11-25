#pragma once 

#include <string>
#include <map>

#include "../lltypes/llsd_value.h"

namespace ticpp { class Node; } //forward declaration

namespace LLSD
{
	namespace detail
	{
		namespace XML 
		{
			struct Parser
			{
				typedef std::string::const_iterator iterator;
				static ValuePtr Parse(iterator it, iterator end);
			protected:
				Parser();
				void InitLookupTable();
				static std::map<std::string, LLSD::ValueType> LookupTable;
				ValuePtr Parse(ticpp::Node * node, bool returnEmpty = false);
				ValuePtr ParseMap(ticpp::Node * node);
				ValuePtr ParseArray(ticpp::Node * node);		
			};

			std::string Build(LLSD::ValuePtr map);
		}
	}
}

