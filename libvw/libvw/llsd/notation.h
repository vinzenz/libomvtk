#ifndef GUARD_LIBVW_LLSD_NOTATION_H_INCLUDED
#define GUARD_LIBVW_LLSD_NOTATION_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "value.h"


namespace vw
{
	namespace detail
	{
		namespace Notation
		{
			struct Parser
			{
				typedef String::const_iterator iterator;
				static LLSDValue Parse(iterator iter, iterator end);		
			};
			String Build(LLSDValue const & data);
		}
	}
}

#endif //GUARD_LIBVW_LLSD_NOTATION_H_INCLUDED
