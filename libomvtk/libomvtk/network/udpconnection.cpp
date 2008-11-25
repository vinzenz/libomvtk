#include "udpconnection.h"
#include "../logger/logger.h"
#include <boost/bind.hpp>

namespace vw
{
	UDPConnection::UDPConnection(ServiceType & ios, PacketReceivedCallback cb, Endpoint const & ep)
		: m_ios(ios)
		, m_endpoint(ep)
		, m_socket(ios, Endpoint(Implementation::v4(), ep.port()))
		, m_on_received(cb)
	{
		listen();
	}

	UDPConnection::~UDPConnection()
	{
		disconnect();
	}	

	UDPConnection::Endpoint const & UDPConnection::endpoint() const
	{
		return m_endpoint;
	}

	UDPConnection::ServiceType & UDPConnection::service() 
	{
		return m_ios;
	}
	
	bool UDPConnection::send(ByteBuffer const & buf)
	{
		SharedBuffer send_buf(new ByteBuffer(buf));
		try
		{
			m_socket.async_send_to
			(
				boost::asio::buffer(*send_buf), 
				m_endpoint,
				boost::bind
				(
					&UDPConnection::sent,
					this,
					send_buf,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
				)
			);
		}
		catch(std::exception const & e)
		{
			LOG_ERR << "Exception caught: " << e.what();
			return false;
		}
		catch(...)
		{
			LOG_ERR << "Unknown exception caught.";
			return false;
		}
		return true;
	}

	void UDPConnection::disconnect()
	{		
		m_socket.close();	
	}

	void UDPConnection::listen()
	{
		try
		{	
			SharedBuffer recv_buf(new ByteBuffer(BUFFER_SIZE,0));
			m_socket.async_receive_from
			(
				boost::asio::buffer(*recv_buf),
				m_endpoint, 
				boost::bind
				(
					&UDPConnection::receive, 
					this, 
					recv_buf,
					boost::asio::placeholders::error, 
					boost::asio::placeholders::bytes_transferred
				)
			);				
		}
		catch(std::exception const & e)
		{
			LOG_ERR << "Exception caught: " << e.what();
		}	
	}	

	void UDPConnection::receive(SharedBuffer buf, boost::system::error_code const & error , std::size_t bytes)
	{
		if(!error)
		{			
			if(m_on_received)
			{
				try
				{
					m_on_received(buf,bytes);
				}
				catch(std::exception const & e)
				{
					LOG_ERR << "Exception caught: " << e.what();
				}
				catch(...)
				{
					LOG_ERR << "Unknown exception caught.";
				}
			}
			// Listen again ;)
			listen();
		}
		else
		{
			LOG_WARN << "Error occurred while receiving udp data. Error code: " << error;
		}
	}

	void UDPConnection::sent(SharedBuffer, boost::system::error_code const & error , std::size_t)
	{
		if(!error)
		{
			LOG_WARN << "Error occurred while sending udp data. Error Code: " << error;
		}
	}
}

