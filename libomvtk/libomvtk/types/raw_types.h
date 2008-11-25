#ifndef GUARD_LIBVW_TYPES_RAW_TYPES_H_INCLUDED
#define GUARD_LIBVW_TYPES_RAW_TYPES_H_INCLUDED


#include <boost/array.hpp>

namespace vw
{
	namespace raw
	{
		struct LLVariable
		{
			ByteBuffer data;
		};
		
		template<size_t N>
		struct LLFixed
		{
			boost::array<Byte,N> data;
		};

		struct LLIPPort
		{
			UInt16 data;
		};

		struct LLIPAddress
		{
			UInt32 data;
		};

		template<typename T>
		struct LLVector3Template
		{
			boost::array<T,3> data;
		};

		typedef LLVector3Template<Real32>  LLVector3;
		typedef LLVector3Template<Real64> LLVector3d;

		struct LLVector4
		{
			boost::array<Real32,4> data;
		};

		struct LLQuaternion
		{
			LLVector3 data;
		};
	}
}

#endif //GUARD_LIBVW_TYPES_RAW_TYPES_H_INCLUDED

