#pragma once
#include <vector>
#include <boost/cstdint.hpp>

#include "../lltypes/llsd_value.h"

namespace LLSD
{
	namespace detail
	{
		namespace Binary
		{
			struct Parser
			{
				typedef std::vector<boost::uint8_t>::const_iterator iterator;
				static ValuePtr Parse(iterator iter, iterator end);
			};

			std::vector<boost::uint8_t> Build(LLSD::ValuePtr data);
		}
	}
}