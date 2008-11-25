#ifndef GUARD_LIBVW_NETWORK_SIMULATOR_H_INCLUDED
#define GUARD_LIBVW_NETWORK_SIMULATOR_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif 

#include "udpconnection.h"
#include "network.h"
#include "simulator_stats.h"            
namespace vw
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

#endif // GUARD_LIBVW_NETWORK_SIMULATOR_H_INCLUDED

