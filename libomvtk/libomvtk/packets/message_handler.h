#ifndef GUARD_LIBOMVTK_PACKETS_MESSAGE_HANDLER_H_INCLUDED
#define GUARD_LIBOMVTK_PACKETS_MESSAGE_HANDLER_H_INCLUDED

#include <boost/function.hpp>
#include "message_handler_manager.h"

namespace omvtk
{
	template<typename MessageT>
	struct MessageHandler : MessageHandlerManager::ConnectionT
	{
		typedef MessageHandlerManager::ConnectionT Base;
		typedef boost::function<void (MessageT const &,Simulator &)> HandlerT;

		MessageHandler()
			: Base(MessageT::id)
			, m_handler()
		{
		}

		MessageHandler(HandlerT const & handler)
			: Base(MessageT::id)
			, m_handler(handler)
		{
		}

		void set(HandlerT const & handler)
		{
			m_handler = handler;
		}

		bool has_handler() const
		{
			return bool(m_handler);
		}

		void call(packets::Message const & msg, Simulator & sender)
		{
			if(m_handler)
			{
				m_handler(static_cast<MessageT const &>(msg),sender);
			}
		}

		void call(packets::Message const & msg, Simulator & sender) const
		{
			if(m_handler)
			{
				m_handler(static_cast<MessageT const &>(msg),sender);
			}
		}
	protected:
		HandlerT m_handler;
	};
}


#endif //GUARD_LIBOMVTK_PACKETS_MESSAGE_HANDLER_MANAGER_H_INCLUDED

