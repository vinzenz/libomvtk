#pragma once

#include <boost/throw_exception.hpp>

struct Location
{
	Location(char const * file, int line)
		: m_file(file), m_line(line)
	{
	}

	Location(Location const & loc)
		: m_file(loc.m_file), m_line(loc.m_line)
	{
	}

	~Location()
	{
	}

	Location & operator=(Location const & loc)
	{
		m_file = loc.m_file;
		m_line = loc.m_line;
		return *this;
	}

	char const * file() const
	{ 
		return m_file; 
	}
	
	int line() const
	{ 
		return m_line; 
	}
protected:
	char const * m_file;
	int m_line;
};

template<typename T, typename U>
inline void LIBVW_ThrowException(Location const & loc, U u)
{
	boost::throw_exception(T(loc, u));
}

template<typename T>
inline void LIBVW_ThrowException(Location const & loc)
{
	boost::throw_exception(T(loc));
}

#define LIBVW_EXCEPTION_LOCATION Location(__FILE__, __LINE__)

#define LIBVW_THROWS_MESSAGE(TYPE, PARAM) \
	LIBVW_ThrowException<TYPE>(LIBVW_EXCEPTION_LOCATION, PARAM)

#define LIBVW_THROWS(TYPE) \
	LIBVW_ThrowException<TYPE>(LIBVW_EXCEPTION_LOCATION)

struct LIBVWException : std::exception
{
	LIBVWException(Location const & loc, char const * message)
		: std::exception(message), m_location(loc)
	{}

	Location const & location() const{ return m_location; }
protected:
	Location m_location;
};

struct NotImplementedError : LIBVWException
{
	NotImplementedError(Location const & loc)
		: LIBVWException(loc, "Operation not implemented!")
	{
	}
};

struct LLSDXmlParseError : LIBVWException
{
	LLSDXmlParseError(Location const & loc)
		: LIBVWException(loc, "Parsing of XML/LLSD failed")
	{}
};

struct LLSDNotationParseError : LIBVWException
{
	LLSDNotationParseError(Location const & loc)
		: LIBVWException(loc, "Parsing of LLSD/Notation failed")
	{}
};

struct LLSDBinaryParseError : LIBVWException
{
	LLSDBinaryParseError(Location const & loc)
		: LIBVWException(loc, "Parsing of Binary LLSD failed")
	{}
};

struct LLSDBinaryBuildError : LIBVWException
{
	LLSDBinaryBuildError(Location const & loc)
		: LIBVWException(loc, "Parsing of Binary LLSD failed")
	{}
};

struct InvalidArgumentException : LIBVWException
{
	InvalidArgumentException(Location const & loc)
		: LIBVWException(loc, "An invalid argument was passed to a function")
	{}
};


