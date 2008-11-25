#ifndef GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_MANAGER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_MANAGER_H_INCLUDED

#include "caps_event.h"
#include "../../utils/connection.h"
#include "../../llsd/value.h"
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>

namespace omvtk
{
	struct Simulator;

	template<CapsEvent EventID>
	struct CapsHandler;

	struct CapsHandlerManager 
	{
		typedef detail::Connection<CapsHandlerManager,CapsEvent> ConnectionT;
		typedef boost::shared_ptr<LLSDValue> LLSDPtr;

		struct Data
		{
			typedef void (*caller_fun_t)(ConnectionT *, LLSDPtr, Simulator &);
			Data()
			: ptr(0)
			, caller_fun(0)
			{}

			template<CapsEvent event_id>
			Data(CapsHandler<event_id> & p)
			: ptr(&p)
			, caller_fun(caller_fun_t(&Data::template caller<event_id>))
			{
			}

			ConnectionT * ptr;						
			caller_fun_t caller_fun;

			template<CapsEvent event_id>
			static void caller(ConnectionT * ptr, LLSDPtr value, Simulator & sender)
			{
				if(ptr)
				(*static_cast<CapsHandler<event_id>*>(ptr))(value,sender);
			}
		};
	
		typedef boost::unordered_map<CapsEvent, Data> HandlerMap;			

		CapsHandlerManager();
		~CapsHandlerManager();

		// Check how many handlers are registered for the given event id
		std::size_t count(CapsEvent event_id) const;
		// Check how many handlers are registered 
		std::size_t size() const;
		// returns true if no handlers are registered
		bool empty() const;

		// Connects a caps event handler
		template<CapsEvent event_id>
		void connect(CapsHandler<event_id> & connection)
		{
			m_handler_map.insert(HandlerMap::value_type(event_id, Data(connection)));	
			connection.connect(*this);
		}

		// Disconnects a handler
		void disconnect(ConnectionT & msg);

		void operator()(CapsEvent event_id, LLSDPtr value, Simulator & sender);
	protected:
		HandlerMap m_handler_map;
	};
}



#endif //GUARD_LIBOMVTK_NETWORK_CAPS_HANDLER_MANAGER_H_INCLUDED

