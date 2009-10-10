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
#ifndef GUARD_LIBOMVTK_NETWORK_SIMULATOR_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_SIMULATOR_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif 

#include "udpconnection.h"
#include "network.h"
#include "simulator_stats.h"            
namespace omvtk
{
#ifndef UNIT_TEST
	struct Simulator
		: boost::noncopyable
	{
		Simulator(Network & network, UDPConnection::Endpoint const & endpoint);
		
		String const & name() const;
		UInt32 sequence();
		bool running() const;

		template<typename MessageT>
		void send_message(MessageT & msg, bool useSequence = false)
		{
			if(useSequence)
			{
				msg.header().sequence(sequence());
			}
			std::size_t bytes = m_connection.send_message(msg);
			if(bytes)
			{
				++m_stats.SentPackets;
				m_stats.SentBytes += bytes;
			}
		}

		bool connect(bool moveToSim);
		void disconnect(bool sendCloseMsg);

	protected:
		void packet_received(UDPConnection::SharedBuffer, std::size_t);

		Network & m_network;
		UDPConnection m_connection;
		UInt32 m_sequence;
		String m_name;		
		bool m_connected;
		SimulatorStats m_stats;
		};
#else
	struct Simulator{ Simulator(){} };
#endif		
}

#endif // GUARD_LIBOMVTK_NETWORK_SIMULATOR_H_INCLUDED

