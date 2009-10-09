#ifndef GUARD_LIBOMVTK_TYPES_EXCEPTIONS_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_EXCEPTIONS_H_INCLUDED

#if _MSC_VER > 100
#	pragma once
#endif

#include <stdexcept>

namespace omvtk
{
	typedef std::runtime_error Exception;	

	struct MalformedPacketException : Exception
	{
		MalformedPacketException()
			: Exception("MalformedPacketException")
		{}
	};

	struct SyntaxException : Exception
	{
		SyntaxException()
			: Exception("SyntaxException")
		{}
		
		SyntaxException(std::string const & msg)
			: Exception("SyntaxException: " + msg)
		{}
	};

	struct IllegalStateException : Exception
	{
		IllegalStateException()
			: Exception("IllegalStateException")
		{}
		
		IllegalStateException(std::string const & msg)
			: Exception("IllegalStateException: " + msg)
		{}

	};

    struct BadCastException : Exception
    {
		BadCastException()
			: Exception("BadCastException")
		{}
		
		BadCastException(std::string const & msg)
			: Exception("BadCastException: " + msg)
		{}
	};

}


#endif //GUARD_LIBOMVTK_TYPES_EXCEPTIONS_H_INCLUDED

