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
#ifndef GUARD_LIBOMVTK_PACKETS_PROCESSORS_H_INCLUDED
#define GUARD_LIBOMVTK_PACKETS_PROCESSORS_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include "serialization.h"

namespace omvtk
{
	namespace packets
	{
		struct BlockSerializationProcessor : boost::noncopyable
		{
			BlockSerializationProcessor(Serializer & s)
				: m_serializer(s)
			{}

			template<typename T>
			void process(T & v, char const *)
			{		
				m_serializer << v;
			}

		protected:
			Serializer & m_serializer;
		};

		struct BlockDeserializationProcessor : boost::noncopyable
		{
			BlockDeserializationProcessor(Deserializer & s)
				: m_deserializer(s)
			{}

			template<typename T>
			void process(T & v, char const *)
			{		
				m_deserializer >> v;
			}

		protected:
			Deserializer & m_deserializer;
		};


		template<typename BlockProcessor>
		struct PacketProcessor : boost::noncopyable
		{
			PacketProcessor(BlockProcessor & processor)
				: m_processor(processor)
			{

			}

			template<typename T>
			void process(T & v, char const *)
			{
				v.process(m_processor);
			}

			template<typename T>
			void process(std::vector<T> & v, char const *)
			{
				Byte count = 0;
				m_processor.process(count, "");
				v.resize(count);
				BOOST_FOREACH(T & t, v)
				{
					t.process(m_processor);
				}
			}

			template<typename T,std::size_t N>
			void process(boost::array<T,N> & v, char const *)
			{
				BOOST_FOREACH(T & t, v)
				{
					t.process(m_processor);
				}
			}
		protected:
			BlockProcessor & m_processor;
		};

		template<typename PacketT>
		void serialize(Serializer & s, PacketT & packet)
		{
			typedef PacketProcessor<BlockSerializationProcessor> Processor;
			BlockSerializationProcessor bp(s);
			Processor p(bp);
			packet.process(p);
		}		
		
		template<typename PacketT>
		void serialize(ByteBuffer & buf, PacketT & packet)
		{
			packet.header().to_bytes(buf);
			Serializer s(buf);
			serialize(s, packet);
			ZeroEncoder<PacketT::encoded>()(buf);
		}

		template<typename PacketT>
		void deserialize(Deserializer & d, PacketT & packet)
		{
			typedef PacketProcessor<BlockDeserializationProcessor> Processor;
			BlockDeserializationProcessor bp(d);
			Processor p(bp);
			packet.process(p);
		}
	}
}

#endif //GUARD_LIBOMVTK_PACKETS_PROCESSORS_H_INCLUDED
