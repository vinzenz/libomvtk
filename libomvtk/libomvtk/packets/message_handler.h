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

