// vim:et:st=4:ts=4:sts=4:
// Copyright (c) 2008,2009 by the OpenMetaverse Toolkit Library Team
// All rights reserved.
//
// - Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Neither the name of the OpenMetaverse Toolkit Library Team nor the names
//   of its contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE
#ifndef GUARD_LIBOMVTK_NETWORK_NETWORK_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_NETWORK_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "../types/lluuid.h"
#include "../packets/message_handler_manager.h"
#include "caps/caps_handler_manager.h"
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace omvtk
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

#endif //GUARD_LIBOMVTK_NETWORK_NETWORK_H_INCLUDED
