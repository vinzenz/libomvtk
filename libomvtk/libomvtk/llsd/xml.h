#ifndef GUARD_LIBOMVTK_LLSD_XML_H_INCLUDED
#define GUARD_LIBOMVTK_LLSD_XML_H_INCLUDED


#if _MSC_VER > 1200
#	pragma once
#endif

#include <string>
#include <map>

#include "value.h"

namespace ticpp { class Node; } //forward declaration

namespace omvtk
{
	namespace detail
	{
		namespace XML 
		{
			struct Parser
			{
				typedef String::const_iterator iterator;
				static LLSDValue Parse(iterator it, iterator end);
			protected:
				Parser();
				void InitLookupTable();
				static std::map<std::string, LLSDValue::Types> LookupTable;
				LLSDValue Parse(ticpp::Node * node, bool returnEmpty = false);
				LLSDValue ParseMap(ticpp::Node * node);
				LLSDValue ParseArray(ticpp::Node * node);		
			};
		}
	}
}

#endif //GUARD_LIBOMVTK_LLSD_XML_H_INCLUDED
