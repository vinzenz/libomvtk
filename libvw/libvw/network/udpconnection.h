#ifndef LIBVW_NETWORK_UDP_CONNECTION_H_INCLUDED
#define LIBVW_NETWORK_UDP_CONNECTION_H_INCLUDED

#include "../types/base_types.h"
#include "../packets/header.h"
#include "../packets/processors.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace vw
{
	struct UDPConnection
		: boost::noncopyable
	{
		typedef boost::asio::ip::udp					Implementation;
		typedef boost::asio::ip::udp::endpoint			Endpoint;
		typedef boost::asio::ip::address				Address;
		typedef UInt16									Port;
		typedef Implementation::socket					Socket;
		typedef boost::asio::io_service					ServiceType;
		enum { BUFFER_SIZE = 8192 };
		typedef boost::shared_ptr<ByteBuffer> 			SharedBuffer;
		typedef boost::function<void (SharedBuffer,std::size_t)	> PacketReceivedCallback;

		UDPConnection(ServiceType & ios, PacketReceivedCallback cb, Endpoint const & ep);
		~UDPConnection();

		Endpoint const & endpoint() const;		
		
		ServiceType & service();

		template<typename MessageT>
		std::size_t send_message(MessageT & msg)
		{
			ByteBuffer buf;		
			packets::serialize(buf, msg);
			if(send(buf))
			{
				return buf.size();
			}
			return 0;
		}

		bool send(ByteBuffer const &);
		void disconnect();
	protected:
		void listen();
		void receive(SharedBuffer, boost::system::error_code const &, std::size_t);
		void sent(SharedBuffer, boost::system::error_code const &, std::size_t);

	protected:
		ServiceType & m_ios;
		Endpoint m_endpoint;
		Socket m_socket;
		PacketReceivedCallback m_on_received;
	};
}

#endif //LIBVW_NETWORK_UDP_CONNECTION_H_INCLUDED
