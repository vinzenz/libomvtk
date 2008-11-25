#ifndef GUARD_LIBOMVTK_NETWORK_CAPS_CAPS_CLIENT_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_CAPS_CAPS_CLIENT_H_INCLUDED

#include "../../types/base_types.h"
#include "../../llsd/value.h"
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace omvtk
{
	struct CapsClient
	{
		typedef boost::shared_ptr<LLSDValue> LLSDValuePtr;
		typedef boost::function< void (LLSDValuePtr) > HandlerType;
		
		CapsClient(HandlerType handler);
		~CapsClient();
	
		void Connect(String const & uri);
		
	protected:
		HandlerType m_handler;
	};
}

#endif //GUARD_LIBOMVTK_NETWORK_CAPS_CAPS_CLIENT_H_INCLUDED

