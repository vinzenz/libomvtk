#ifndef GUARD_LIBOMVTK_PACKETS_SERIALIZATION_H_INCLUDED
#define GUARD_LIBOMVTK_PACKETS_SERIALIZATION_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "../types/sub_range.h"
#include "../types/raw_types.h"
#include "../llsd/value.h"
#include "header.h"
#include <Poco/ByteOrder.h>
#include <boost/noncopyable.hpp>

namespace omvtk
{
	namespace packets
	{
		struct NullType{};

		inline std::size_t zero_encode(ByteBuffer & src)
		{
			if(src.size() < 6)
			{
				return 0;
			}

			try
			{
				std::size_t srclen = src.size();
				Int32 bodylen = Int32(srclen);
				if(src.front() & MSG_APPENDED_ACKS)
				{
					bodylen -= Int32(src.back()) * 4 + 1;
				}

				ByteBuffer dest;
				dest.reserve(src.size() * 2);
				dest.insert(dest.end(),src.begin(), src.begin() + 6);

				Int32 i = 6;
				for (; i < bodylen; i++) 
				{
					if (src.at(i) == 0) 
					{
						Byte cnt = 0;
						while(++i < bodylen && src.at(i) == 0)
						{
							++cnt;
							if(cnt == 0)
							{
								dest.push_back(0);
								dest.push_back(0xff);
							}
						}
						if(cnt)
						{
							dest.push_back(0);								
							dest.push_back(cnt);						
						}
					} 

					if(i >= bodylen)
					{
						break;
					}
					dest.push_back(src.at(i));
				}
				
				// Now append the acks
				std::size_t data_len = dest.size();				
				for(;i < Int32(srclen); ++i)
				{
					dest.push_back(src.at(i));
				}

				// Swapping buffers 
				src.swap(dest);							
				return data_len;
			}
			catch (std::exception const &)
			{
				
			}
			return 0;
		}

		inline void zero_decode_impl(ByteBuffer & src, ByteBuffer & dest, std::size_t start, std::size_t maxCount)
		{
			dest.insert(dest.end(), src.begin(), src.begin()+ std::min<std::size_t>(6,maxCount));
			for (size_t i = start; i < maxCount; i++) 
			{
				if (src.at(i) == 0) 
				{				
					if(++i < maxCount)
					{
						dest.insert(dest.end(), std::size_t(src.at(i))+1, 0);
					}
				} 
				else 
				{
					dest.push_back(src.at(i));
				}
			}
		}
		
		inline void zero_decode_command(ByteBuffer & src, ByteBuffer & dest)
		{
			try
			{				
				std::size_t srclen = std::min<std::size_t>(src.size(), 10);
				zero_decode_impl(src, dest, 6, srclen);
				src.swap(dest);
			}
			catch (std::exception const &)
			{

			}	
		}

		inline void zero_decode(ByteBuffer & src)
		{
			try
			{
				ByteBuffer dest;
				dest.reserve(0x2000);
				std::size_t srclen = src.size();
				zero_decode_impl(src, dest, 6, srclen);
				src.swap(dest);
			}
			catch (std::exception const &)
			{
				
			}			
		}

		template<bool Encode = false>
		struct ZeroEncoder
		{
			void operator()(ByteBuffer & )
			{}
		};

		template<>
		struct ZeroEncoder<true>
		{
			void operator()(ByteBuffer & buf)
			{
				zero_encode(buf);
			}
		};

		struct Serializer : boost::noncopyable
		{
			typedef ByteBuffer Buffer;
				
			Serializer(Buffer & buf)
				: m_buffer(buf)
			{
			}

			template<typename Iterator>
			inline Serializer & write(Iterator it, Iterator end)			
			{
				m_buffer.insert(m_buffer.end(), it, end);
				return *this;
			}
			
			template<typename Container>
			inline Serializer & write(Container const & c)
			{
				return write(c.begin(), c.end());
			}

		protected:
			Buffer & m_buffer;
		};

		struct Deserializer : boost::noncopyable
		{
			typedef ByteBuffer Buffer;
			
			Deserializer(Buffer & buf, std::size_t offset = 0)
				: m_buffer(buf)		
				, m_offset(offset)
			{
			}

			template<typename Container>
			inline Deserializer & read(Container & buf)
			{
				BOOST_STATIC_ASSERT(byte_sub_range::iterator_check<typename Container::iterator>::value);				
				return read(&buf[0],buf.size());
			}

			inline Deserializer & read(Byte * p, size_t length)
			{
				libomvtk_ensure(m_buffer.size() >= m_offset);
				libomvtk_ensure(m_buffer.size() - m_offset >= length);
				memcpy(p,&m_buffer[m_offset],length);
				m_offset += length;
				return *this;
			}
		protected:
			Buffer & m_buffer;
			size_t m_offset;
		};

		inline Real64 RealToNetwork(Real64 r)
		{
			return Real64ByteOrder::convert(Poco::ByteOrder::toNetwork,r);
		}

		inline Real32 RealToNetwork(Real32 r)
		{
			return Real32ByteOrder::convert(Poco::ByteOrder::toNetwork,r);
		}

		inline Real64 RealFromNetwork(Real64 r)
		{
			return Real64ByteOrder::convert(Poco::ByteOrder::fromNetwork,r);
		}

		inline Real32 RealFromNetwork(Real32 r)
		{
			return Real32ByteOrder::convert(Poco::ByteOrder::fromNetwork,r);
		}

		// every compiler should be able to optimize this away :)
		template<typename T>
		inline T & NoConvert(T & t)
		{
			return t;
		}

#define LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_IMPL(STYPE,TO_NET,FROM_NET) \
		inline Serializer & operator << (Serializer & s, STYPE value) \
		{ \
			value = TO_NET(value); \
			Byte const * p = reinterpret_cast<Byte const *>(&value); \
			return s.write(byte_sub_range(p, p + sizeof(STYPE))); \
		} \
		inline Deserializer & operator >> (Deserializer & d, STYPE & value) \
		{ \
			Byte * p = reinterpret_cast<Byte*>(&value); \
			d.read(p,sizeof(STYPE)); \
			value = FROM_NET(value); \
			return d; \
		}

#define LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER(STYPE) \
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_IMPL(STYPE,NoConvert,NoConvert)
#define LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(STYPE) \
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_IMPL(STYPE,Poco::ByteOrder::toNetwork,Poco::ByteOrder::fromNetwork)

		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER(Int8)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(Int16)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(Int32)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(Int64)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER(UInt8)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(UInt16)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(UInt32)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_BYTEORDER(UInt64)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_IMPL(Real32,RealToNetwork,RealFromNetwork)
		LIBOMVTK_PACKETS_IMPLEMENT_GENERIC_SERIALIZER_IMPL(Real64,RealToNetwork,RealFromNetwork)

		inline Serializer & operator<<(Serializer & s, bool val)
		{
			return s << Byte(val ? '1' : '0');			
		}
		inline Deserializer & operator>>(Deserializer & d, bool & val)
		{
			Byte b = 0;
			d >> b;			
			val = (b == '1');
			return d;
		}

		inline Serializer & operator<<(Serializer & s, NullType const &)
		{
			return s;
		}
		inline Deserializer & operator>>(Deserializer & d, NullType &)
		{
			return d;
		}

		inline Serializer & operator<<(Serializer & s, LLUUID const & v)
		{
			return s.write(v.to_binary());
		}

		inline Deserializer & operator>>(Deserializer & d, LLUUID & v)
		{
			boost::array<Byte,16> buf = {{0}};
			d.read(buf);
			v = LLUUID(byte_sub_range(buf.begin(),buf.end()));
			return d;
		}

		inline Serializer & operator<<(Serializer & s, ByteBuffer & buf)
		{
			return s.write(buf);
		}

		inline Serializer & operator<<(Serializer & s, raw::LLVariable const & v)
		{
			// must be between 0 and 255
			libomvtk_ensure(v.data.size() < 256);
			return s << Byte(v.data.size()) << v.data;
		}

		inline Deserializer & operator>>(Deserializer & d, raw::LLVariable & v)
		{
			Byte size = 0;
			d >> size;
			v.data.resize(size,0);
			d.read(v.data);
			return d;
		}

		template<size_t N>
		inline Serializer & operator<<(Serializer & s, raw::LLFixed<N> const & v)
		{			
			return s.write(v.data);
		}

		template<size_t N>
		inline Deserializer & operator>>(Deserializer & d, raw::LLFixed<N> & v)
		{
			return d.read(v.data);
		}

		inline Serializer & operator<<(Serializer & s, raw::LLIPAddress const & v)
		{			
			return s << v.data;
		}

		inline Deserializer & operator>>(Deserializer & d, raw::LLIPAddress & v)
		{
			return d >> v.data;
		}

		inline Serializer & operator<<(Serializer & s, raw::LLIPPort const & v)
		{
			return s << v.data;
		}

		inline Deserializer & operator>>(Deserializer & d, raw::LLIPPort & v)
		{
			return d >> v.data;
		}

		template<typename Type>
		inline Serializer & operator<<(Serializer & s, raw::LLVector3Template<Type> const & v)
		{
			return s << v.data[0] << v.data[1] << v.data[2];
		}

		template<typename Type>
		inline Deserializer & operator>>(Deserializer & d, raw::LLVector3Template<Type> & v)
		{
			return d >> v.data[0] >> v.data[1] >> v.data[2];
		}

		inline Serializer & operator<<(Serializer & s, raw::LLVector4 const & v)
		{
			return s << v.data[0] << v.data[1] << v.data[2] << v.data[3];
		}

		inline Deserializer & operator>>(Deserializer & d, raw::LLVector4 & v)
		{
			return d >> v.data[0] >> v.data[1] >> v.data[2] >> v.data[3];
		}

		inline Serializer & operator<<(Serializer & s, raw::LLQuaternion const & v)
		{
			return s << v.data;
		}

		inline Deserializer & operator>>(Deserializer & d, raw::LLQuaternion & v)
		{
			return d >> v.data;
		}		
	}
}


#endif //GUARD_LIBOMVTK_PACKETS_SERIALIZATION_H_INCLUDED
