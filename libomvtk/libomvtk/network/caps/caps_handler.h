#ifndef GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_H_INCLUDED

#include "caps_handler_manager.h"

namespace omvtk
{
	template<CapsEvent event_id>
	struct CapsHandler : CapsHandlerManager::ConnectionT
	{
		typedef CapsHandlerManager::ConnectionT Base;
		typedef CapsHandlerManager::LLSDPtr LLSDPtr;
		typedef boost::function<void(LLSDPtr,Simulator&)> Handler;

		CapsHandler()
		: Base(event_id)
		, m_handler()
		{}

		CapsHandler(Handler const & handler)
		: Base(event_id)
		, m_handler(handler)
		{}

		void operator()(LLSDPtr value, Simulator & sender)
		{
			if(m_handler)
			{
				m_handler(value, sender);	
			}		
		}

	protected:
		Handler m_handler;
	}
}

#endif //GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_H_INCLUDED

