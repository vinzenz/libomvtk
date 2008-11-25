#ifndef GUARD_LIBVW_NETWORK_NETWORK_H_INCLUDED
#define GUARD_LIBVW_NETWORK_NETWORK_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "../types/lluuid.h"
#include "../packets/message_handler_manager.h"
#include "caps/caps_handler_manager.h"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace vw
{
	namespace packets
	{
		struct UseCircuitCodeMessage;
	}
	struct GridClient;
	struct Network 
		: boost::noncopyable
	{
		struct HandlerManager
		{
			CapsHandlerManager & caps()
			{ 
				return m_caps; 
			}

			CapsHandlerManager const & caps() const 
			{
				return m_caps; 
			}
			
			MessageHandlerManager & messages()
			{
				return m_messages; 
			}
			
			MessageHandlerManager const & messages() const 
			{
				return m_messages; 
			}
		protected:
			CapsHandlerManager m_caps;
			MessageHandlerManager m_messages;
		};

		Network(GridClient & client);
		~Network();

		LLUUID id() const;
		void id(LLUUID const &);
		
		LLUUID session_id() const;		
		void session_id(LLUUID const &);

		void circuit_code(UInt32 code);
		UInt32 circuit_code() const;

		boost::asio::io_service & service();
		boost::asio::io_service const & service() const;
		boost::asio::ssl::context & context();
		boost::asio::ssl::context const & context() const;
		
		MessageHandlerManager & messages_manager();
		CapsHandlerManager & caps_manager();

		void get_circuit_code(packets::UseCircuitCodeMessage&);
	
		void shutdown();			

		HandlerManager const & handler() const;
		HandlerManager & handler();
	protected:
		GridClient & m_client;
		HandlerManager m_handler_manager;		
		LLUUID m_id;
		LLUUID m_session_id;
		UInt32 m_circuit_code;
	};
}

#endif //GUARD_LIBVW_NETWORK_NETWORK_H_INCLUDED
