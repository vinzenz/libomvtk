#if _MSC_VER > 1200
#	pragma warning(push)
#	pragma warning(disable:4127)
#	pragma warning(disable:4512)
#endif

#include "simulator.h"
#include "message_builder.h"
#include "../packets/packets.h"
#include "../packets/serialization.h"
#include "../logger/logger.h"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

namespace vw
{
	Simulator::Simulator(Network & network, UDPConnection::Endpoint const & endpoint)
		: m_network(network)
		, m_connection(network.service(), boost::bind(&Simulator::packet_received, this, _1, _2), endpoint)
		, m_sequence(0)
		, m_name()
		, m_connected(false)
		, m_stats()
	{
	}

	String const & Simulator::name() const
	{
		return m_name;
	}

	UInt32 Simulator::sequence()
	{
		return m_sequence++;
	}

	bool Simulator::running() const
	{
		return m_connected;
	}

	bool Simulator::connect(bool moveToSim)
	{
		try
		{
			if(!m_connected)
			{		
				packets::UseCircuitCodeMessage msg;
				m_network.get_circuit_code(msg);
				m_connected = m_connection.send_message(msg) != 0;
			}
			else
			{
				// Log: Attempt to connect to a simulator we're already connected to				
			}
				
			if(m_connected && moveToSim)
			{
				//TODO: Complete Agent Movement
			}
			
			return true;
		}
		catch(std::exception const & e)
		{
			LOG_ERR << "Exception caught: " << e.what();
		}
		catch(...)
		{
			LOG_ERR << "Unknown exception caught.";
		}
		return false;
	}

	void Simulator::packet_received(UDPConnection::SharedBuffer buf, std::size_t bytes)
	{
		try
		{
			if(bytes >= 10)
			{
				ByteBuffer tmp;
				ByteBuffer & buffer = *buf;
				if(buffer[0] & packets::MSG_ZEROCODED)
				{
					tmp.reserve(8192);
					packets::zero_decode_command(buffer, tmp);
				}
				else
				{
					tmp.assign(buf->begin(), buf->begin() + bytes);
				}
				tmp.swap(buffer);
				
				UInt32 id = 0;
				if(buffer[6] == 0xFF)
				{
					if(buffer[7] == 0xFF)
					{
						id = ( UInt32(buffer[8]) << 8 ) | buffer[9];
					}
					else
					{
						id = 0xFF000000 | buffer[8];
					}
				}
				else
				{
					id = buffer[6];
				}
	
				build_message(*this, m_network, buffer, id);
				
				m_stats.RecvBytes += buffer.size();
				++m_stats.RecvPackets;
			}
		}
		catch(std::exception const & e)
		{
			LOG_ERR << "Exception caught: " << e.what();
		}
		// don't let any exception cross because it might kill the thread		
		catch(...)
		{
			LOG_ERR << "Unknown exception caught.";
		}
	}

	void Simulator::disconnect(bool sendCloseMsg)
	{
		if(m_connected)
		{
			m_connected = false;
		
			if(sendCloseMsg)
			{	
				packets::CloseCircuitMessage msg;
				send_message(msg);
			}

			m_connection.disconnect();	
		}
	}
}

#if _MSC_VER > 1200
#	pragma warning(pop)
#endif
