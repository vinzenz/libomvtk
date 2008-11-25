#ifndef GUARD_LIBVW_PACKETS_PROCESSORS_H_INCLUDED
#define GUARD_LIBVW_PACKETS_PROCESSORS_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <boost/array.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include "serialization.h"

namespace vw
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

#endif //GUARD_LIBVW_PACKETS_PROCESSORS_H_INCLUDED
