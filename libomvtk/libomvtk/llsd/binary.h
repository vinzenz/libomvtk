#ifndef GUARD_LIBOMVTK_LLSD_BINARY_H_INCLUDED
#define GUARD_LIBOMVTK_LLSD_BINARY_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "value.h"

namespace omvtk
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

#endif //GUARD_LIBOMVTK_LLSD_BINARY_H_INCLUDED
