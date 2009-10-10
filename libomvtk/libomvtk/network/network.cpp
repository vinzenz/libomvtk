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
#include "network.h"
#include "../packets/packets.h"
#include "../gridclient.h"

namespace omvtk
{

	Network::Network(GridClient & client)
		: m_client(client)
		, m_handler_manager()
		, m_id()
		, m_session_id()
		, m_circuit_code(~UInt32(0))
	{
	}

	Network::~Network()
	{
	}

	LLUUID Network::id() const
	{
		return m_id;
	}
	
	void Network::id(LLUUID const & id_)
	{
		m_id = id_;
	}

	LLUUID Network::session_id() const
	{
		return m_session_id;
	}
	
	void Network::session_id(LLUUID const & sess_id)
	{
		m_session_id = sess_id;
	}

	UInt32 Network::circuit_code() const
	{
		return m_circuit_code;
	}

	void Network::circuit_code(UInt32 code)
	{
		m_circuit_code = code;
	}

	boost::asio::io_service & Network::service()
	{
		return m_client.library().service();
	}

	boost::asio::io_service const & Network::service() const
	{
		return m_client.library().service();
	}

	boost::asio::ssl::context & Network::context()
	{
		return m_client.library().context();
	}

	boost::asio::ssl::context const & Network::context() const
	{
		return m_client.library().context();
	}

	Network::HandlerManager const & Network::handler() const
	{
		return m_handler_manager;
	}
	
	Network::HandlerManager & Network::handler()
	{
		return m_handler_manager;
	}
	
	void Network::get_circuit_code(packets::UseCircuitCodeMessage& msg)
	{
		msg.CircuitCode.Code = m_circuit_code;
		msg.CircuitCode.SessionID = m_session_id;
		msg.CircuitCode.ID = m_id;
	}		
}
