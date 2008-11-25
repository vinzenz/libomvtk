#ifndef GUARD_LIBVW_TYPES_BASE_TYPES_H_INCLUDED
#define GUARD_LIBVW_TYPES_BASE_TYPES_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <string>
#include <vector>
#include <Poco/Types.h>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <ostream>
#include <istream>

namespace vw
{
	typedef Poco::Int8  Int8;
	typedef Poco::Int16 Int16;
	typedef Poco::Int32 Int32;
	typedef Poco::Int64 Int64;

	typedef Poco::UInt8  UInt8;
	typedef Poco::UInt16 UInt16;
	typedef Poco::UInt32 UInt32;
	typedef Poco::UInt64 UInt64;

	typedef UInt8  Byte;
	typedef UInt16 Word;
	typedef UInt32 DWord;
	typedef UInt64 QWord;

	typedef float  Real32;
	typedef double Real64;

	typedef std::vector<Byte> ByteBuffer;

	typedef std::string  String;

	template<typename RealT, typename IntT>
	struct RealTByteOrderHelper
	{

		union help
		{
			IntT i;
			RealT r;
		};

		static RealT convert(IntT (*f)(IntT), RealT r)
		{
			help h;
			h.r = r;
			h.i = f(h.i);
			return h.r;
		}
	};

	typedef RealTByteOrderHelper<Real64,UInt64> Real64ByteOrder; 
	typedef RealTByteOrderHelper<Real32,UInt32> Real32ByteOrder; 
}

namespace std
{
	inline std::ostream & operator<<(std::ostream & os, vw::ByteBuffer const & v)
	{
		BOOST_FOREACH(vw::Byte const & b, v)
		{
			os << (int(b));
		}
		return os;
	}
}

#endif //GUARD_LIBVW_TYPES_BASE_TYPES_H_INCLUDED

