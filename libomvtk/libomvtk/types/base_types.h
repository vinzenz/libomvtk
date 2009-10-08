#ifndef GUARD_LIBOMVTK_TYPES_BASE_TYPES_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_BASE_TYPES_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include <string>
#include <vector>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/cstdint.hpp>
#include <ostream>
#include <istream>

namespace omvtk
{
	typedef boost::int8_t  Int8;
	typedef boost::int16_t Int16;
	typedef boost::int32_t Int32;
	typedef boost::int64_t Int64;

	typedef boost::uint8_t  UInt8;
	typedef boost::uint16_t UInt16;
	typedef boost::uint32_t UInt32;
	typedef boost::uint64_t UInt64;

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
	inline std::ostream & operator<<(std::ostream & os, omvtk::ByteBuffer const & v)
	{
		BOOST_FOREACH(omvtk::Byte const & b, v)
		{
			os << (int(b));
		}
		return os;
	}
}

#endif //GUARD_LIBOMVTK_TYPES_BASE_TYPES_H_INCLUDED

