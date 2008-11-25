#ifndef GUARD_LIBVW_LLSD_BINARY_H_INCLUDED
#define GUARD_LIBVW_LLSD_BINARY_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "value.h"

namespace vw
{
	namespace detail
	{
		namespace Binary
		{
			struct Parser
			{
				typedef LLSDValue::Binary::const_iterator iterator;
				static LLSDValue Parse(iterator iter, iterator end);
			};

			LLSDValue::Binary Build(LLSDValue const & data);
		}
	}
}

#endif //GUARD_LIBVW_LLSD_BINARY_H_INCLUDED
