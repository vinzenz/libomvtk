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
#ifndef GUARD_LIBOMVTK_PACKETS_HEADER_H_INCLUDED
#define GUARD_LIBOMVTK_PACKETS_HEADER_H_INCLUDED

#if _MSC_VER > 1200
#    pragma once
#endif

#include "../types/base_types.h"
#include "../types/exceptions.h"
#include "../types/assert.h"
#include <boost/shared_ptr.hpp>
#include <cstring>

namespace omvtk
{
    namespace packets
    {        
        //Taken from libomv
        enum MessageFlags
        {            
            /// This header flag signals that ACKs are appended to the packet
            MSG_APPENDED_ACKS = 0x10,
            /// This header flag signals that this packet has been sent before
            MSG_RESENT = 0x20,
            /// This header flags signals that an ACK is expected for this packet
            MSG_RELIABLE = 0x40,
            /// This header flag signals that the message is compressed using zerocoding
            MSG_ZEROCODED = 0x80
        };

        enum FrequencyType
        {
            FT_LOW,
            FT_MEDIUM,
            FT_HIGH,
            FT_FIXED
        };

        struct Header
        {
            Header(Header const & h)
                : m_data(h.m_data)
                , m_frequency(h.m_frequency)
                , m_acks(h.m_acks)
            {}

            Header & operator=(Header h)
            {
                swap(h);
                return *this;
            }

        protected:
            Header(FrequencyType frequency, std::size_t header_size)
                : m_data(header_size,0)
                , m_frequency(frequency)
                , m_acks()
            {

            }

            Header(FrequencyType frequency, std::size_t header_size, ByteBuffer & buffer, std::size_t & pos)
                : m_data(header_size,0)
                , m_frequency(frequency)
                , m_acks()
            {
                if(buffer.size() < header_size)
                {
                    boost::throw_exception(MalformedPacketException());
                }
                from_bytes(buffer, pos);
            }

        public:

            Byte flags() const 
            { 
                return m_data.front(); 
            }
        
            void flags(Byte f)
            { 
                m_data.front() = f;
            }

            bool appended_acks() const 
            { 
                return test_flag(MSG_APPENDED_ACKS);
            }
            
            void appended_acks(bool set) 
            { 
                change_flag(MSG_APPENDED_ACKS, set);
            }

            bool resent() const
            {
                return test_flag(MSG_RESENT);
            }

            void resent(bool set)
            {
                change_flag(MSG_RESENT, set);
            }
            
            bool reliable() const
            {
                return test_flag(MSG_RELIABLE);
            }

            void reliable(bool set)
            {
                change_flag(MSG_RELIABLE, set);
            }

            bool encoded() const
            {
                return test_flag(MSG_ZEROCODED);
            }

            void encoded(bool set)
            {
                change_flag(MSG_ZEROCODED, set);
            }

            FrequencyType frequency() const 
            {
                return m_frequency;
            }

            Int32 sequence() const
            {
                return *reinterpret_cast<Int32 const*>(&m_data[1]);
            }
            
            void sequence(Int32 value)
            {
                *reinterpret_cast<Int32*>(&m_data[1]) = value;
            }

            std::vector<UInt32> const & acklist() const
            {
                return m_acks;
            }

            std::vector<UInt32> & acklist() 
            {
                return m_acks;
            }

            void create_acklist(ByteBuffer & buffer)
            {
                if(appended_acks())
                {
                    if(buffer.empty() || buffer.back() * 4u > buffer.size() - 1) 
                    {
                        boost::throw_exception(MalformedPacketException());
                    }

                    try
                    {
                        std::size_t count = buffer.back();
                        count *= 4;

                        m_acks.resize(count);
                        buffer.pop_back();
                        std::size_t index = m_acks.size() - (count + 1);
                        libomvtk_assert(m_acks.size() > index);
                        std::memcpy(&m_acks[0], &buffer[index], count);
                        buffer.erase(buffer.begin() + count, buffer.end());
                    }
                    catch (...)
                    {
                        boost::throw_exception(MalformedPacketException());
                    }
                }
            }

            UInt16 id() const
            {
                if(8 - m_frequency)
                {
                    return *reinterpret_cast<UInt16 const *>(&m_data[8]);
                }
                return UInt16(m_data[8 - m_frequency]);
            }

            void id(UInt16 i)
            {
                if(8 - m_frequency)
                {
                    *reinterpret_cast<UInt16*>(&m_data[8]) = i;
                }
                else
                {
                    m_data[8 - m_frequency] = Byte(i);
                }
            }

            void to_bytes(ByteBuffer & buffer) const
            {
                buffer.insert(buffer.end(), m_data.begin(), m_data.end());
            }
            
            std::size_t size() const
            {
                return m_data.size();
            }

            void swap(Header & hdr) throw()
            {
                m_data.swap(hdr.m_data);
                m_acks.swap(hdr.m_acks);
                std::swap(hdr.m_frequency, m_frequency);
            }

        protected:
            void change_flag(Byte flag, bool set)
            {
                if(set)
                {
                    m_data.front() |= flag;
                }
                else
                {
                    m_data.front() &= ~flag;
                }
            }

            bool test_flag(Byte flag) const
            {
                return (flags() & flag) == flag;
            }
        protected:
            ByteBuffer m_data;
            FrequencyType m_frequency;
            std::vector<UInt32> m_acks;

        private:
            void from_bytes(ByteBuffer & buffer, std::size_t & pos)
            {
                memcpy(&m_data[0],&buffer[0],size());
                if (m_frequency == FT_LOW && (buffer[0] & MSG_ZEROCODED) != 0 && buffer[8] == 0)
                {
                    if (buffer[9] == 1)
                    {
                        m_data[9] = buffer[10];
                    }
                    else
                    {
                        boost::throw_exception(MalformedPacketException());
                    }
                }
                pos = size();
                create_acklist(buffer);
            }
        };

        struct LowHeader : Header
        {
            LowHeader()
                : Header(FT_LOW, 10)
            {
                m_data[6] = m_data[7] = 0xFF;
            }

            LowHeader(ByteBuffer & buffer, std::size_t & pos)
                : Header(FT_LOW, 10, buffer, pos)
            {
                m_data[6] = m_data[7] = 0xFF;
            }
        };

        struct MediumHeader : Header
        {
            MediumHeader()
                : Header(FT_MEDIUM, 8)
            {
                m_data[6] = 0xFF;
            }

            MediumHeader(ByteBuffer & buffer, std::size_t & pos)
                : Header(FT_MEDIUM, 8, buffer, pos)
            {
                m_data[6] = 0xFF;                
            }
        };

        struct HighHeader : Header
        {
            HighHeader()
                : Header(FT_HIGH, 7)
            {                
            }

            HighHeader(ByteBuffer & buffer, std::size_t & pos)
                : Header(FT_HIGH, 7, buffer, pos)
            {
            }
        };

        struct Message
        {
            Message(Header const & hdr)
                : m_header(hdr)
            {
            }

            Message(Message const & msg)
                : m_header(msg.m_header)
            {
            }

            Message & operator=(Message msg)
            {
                swap(msg);
                return *this;
            }

            Header & header()
            {
                return m_header;
            }

            Header const & header() const
            {
                return m_header;
            }

            void swap(Message & msg) throw()
            {
                m_header.swap(msg.m_header);
            }
        protected:
            Header m_header;
        };
    }
}

#endif //GUARD_LIBOMVTK_PACKETS_HEADER_H_INCLUDED
