#pragma once
#include <boost/cstdint.hpp>
#include <Poco/ByteOrder.h>

namespace LLSD 
{
	namespace detail
	{
		union ByteOrderHelper
		{
			boost::uint64_t i;
			double f;
		};
		inline boost::uint16_t to_host(boost::uint16_t value)
		{
			return Poco::ByteOrder::fromNetwork(Poco::UInt16(value));
		}

		inline boost::uint32_t to_host(boost::uint32_t value)
		{
			return Poco::ByteOrder::fromNetwork(Poco::UInt32(value));
		}

		inline boost::uint64_t to_host(boost::uint64_t value)
		{
			return Poco::ByteOrder::fromNetwork(Poco::UInt64(value));
		}

		inline boost::int16_t to_host(boost::int16_t value)
		{
			return Poco::ByteOrder::fromNetwork(Poco::Int16(value));
		}

		inline boost::int32_t to_host(boost::int32_t value)
		{
			return Poco::ByteOrder::fromNetwork(Poco::Int32(value));
		}

		inline boost::int64_t to_host(boost::int64_t value)
		{
			return Poco::ByteOrder::fromNetwork(Poco::Int64(value));
		}

		inline double to_host(double value)
		{
			ByteOrderHelper helper;
			helper.f = value;
			helper.i = to_host(helper.i);
			return helper.f;
		}

		inline boost::uint16_t to_network(boost::uint16_t value)
		{			
			return Poco::ByteOrder::toNetwork(Poco::UInt16(value));
		}

		inline boost::uint32_t to_network(boost::uint32_t value)
		{			
			return Poco::ByteOrder::toNetwork(Poco::UInt32(value));
		}

		inline boost::uint64_t to_network(boost::uint64_t value)
		{			
			return Poco::ByteOrder::toNetwork(Poco::UInt64(value));
		}

		inline boost::int16_t to_network(boost::int16_t value)
		{			
			return Poco::ByteOrder::toNetwork(Poco::Int16(value));
		}

		inline boost::int32_t to_network(boost::int32_t value)
		{			
			return Poco::ByteOrder::toNetwork(Poco::Int32(value));
		}

		inline boost::int64_t to_network(boost::int64_t value)
		{			
			return Poco::ByteOrder::toNetwork(Poco::Int64(value));
		}

		inline double to_network(double value)
		{
			ByteOrderHelper helper;
			helper.f = value;
			helper.i = to_network(helper.i);
			return helper.f;
		}
	}
}