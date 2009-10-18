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
#ifndef LIBOMVTK_NETWORK_UDP_CONNECTION_H_INCLUDED
#define LIBOMVTK_NETWORK_UDP_CONNECTION_H_INCLUDED

#include "../types/base_types.h"
#include "../packets/header.h"
#include "../packets/processors.h"
#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace omvtk
{
    struct UDPConnection
        : boost::noncopyable
    {
        typedef boost::asio::ip::udp                    Implementation;
        typedef boost::asio::ip::udp::endpoint            Endpoint;
        typedef boost::asio::ip::address                Address;
        typedef UInt16                                    Port;
        typedef Implementation::socket                    Socket;
        typedef boost::asio::io_service                    ServiceType;
        enum { BUFFER_SIZE = 8192 };
        typedef boost::shared_ptr<ByteBuffer>             SharedBuffer;
        typedef boost::function<void (SharedBuffer,std::size_t)    > PacketReceivedCallback;

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

#endif //LIBOMVTK_NETWORK_UDP_CONNECTION_H_INCLUDED
