#include "stdafx.h"
#include "llsd_string.h"
#include "llsd_integer.h"
#include "llsd_real.h"
#include "llsd_date.h"
#include "llsd_uuid.h"
#include "llsd_uri.h"
#include "llsd_boolean.h"
#include "llsd_binary.h"
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/time_parsers.hpp>

namespace LLSD
{
	String::String()
		: Value(VTID_STRING)
		, m_value()
	{
	}

	String::String(std::string const & o)
		: Value(VTID_STRING)
		, m_value(o)
	{
	}

	String::String(String const & o)
		: Value(VTID_STRING)
		, m_value(o.m_value)
	{
	}

	String::String(StringPtr const & o)
		: Value(VTID_STRING)
		, m_value(o ? o->m_value : std::string())
	{
	}

	String::~String()
	{
	}


	String & String::operator=(String o)
	{
		std::swap(o.m_value, m_value);
		return *this;
	}


	std::string const & String::GetValue() const
	{
		return m_value;
	}

	void String::SetValue(std::string const & val)
	{
		m_value = val;
	}


	IntegerPtr String::ToInteger() const
	{
		boost::uint32_t val  = 0; 
		try
		{
			val = boost::lexical_cast<boost::uint32_t>(m_value);
		}
		catch(...)
		{
			// Ignore any conversion errors
		}
		return IntegerPtr(new Integer(val));
	}

	RealPtr String::ToReal() const
	{
		double val  = 0.0; 
		try
		{
			val = boost::lexical_cast<double>(m_value);
		}
		catch(...)
		{
			// Ignore any conversion errors
		}
		return RealPtr(new Real(val));
	}

	StringPtr String::ToString() const
	{
		return StringPtr(new String(*this));
	}

	DatePtr String::ToDate() const
	{
		boost::posix_time::ptime val;
		try
		{
			val = boost::posix_time::from_iso_string(m_value);
		}
		catch (...)
		{
			
		}
		return DatePtr(new Date(val));		
	}

	UUIDPtr String::ToUUID() const
	{
		return UUIDPtr(new UUID(m_value));
	}

	BooleanPtr String::ToBoolean() const
	{
		return BooleanPtr(new Boolean(!m_value.empty()));
	}

	BinaryPtr String::ToBinary() const
	{
		return BinaryPtr(new Binary(reinterpret_cast<boost::uint8_t const*>(&m_value[0]), m_value.size()));
	}

	UriPtr String::ToUri() const
	{
		return UriPtr(new Uri(m_value));
	}
}