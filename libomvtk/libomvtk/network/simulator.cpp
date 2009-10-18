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
#if _MSC_VER > 1200
#    pragma warning(push)
#    pragma warning(disable:4127)
#    pragma warning(disable:4512)
#   pragma warning(disable:4355) // this in initalization list 
#endif

#include "simulator.h"
#include "message_builder.h"
#include "../packets/packets.h"
#include "../packets/serialization.h"
#include "../logger/logger.h"
#include <boost/bind.hpp>
#include <boost/asio/placeholders.hpp>

namespace omvtk
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
#    pragma warning(pop)
#endif
