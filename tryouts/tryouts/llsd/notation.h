#pragma once 

#include "../lltypes/llsd_value.h"


namespace LLSD
{
	namespace detail
	{
		namespace Notation
		{
			struct Parser
			{
				typedef std::string::const_iterator iterator;
				static ValuePtr Parse(iterator iter, iterator end);		
			};
			std::string Build(LLSD::ValuePtr data);
		}
	}
}