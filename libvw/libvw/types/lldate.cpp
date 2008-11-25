#include "lldate.h"

#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeParser.h>
#include <Poco/ByteOrder.h>

namespace 
{
	vw::LLDate::value_type FromByteSubRange(vw::byte_sub_range const & sr)
	{
		libvw_ensure(sr.size() == sizeof(vw::Real64));
		vw::Real64 r = *(vw::Real64*)&sr[0];
		r = vw::Real64ByteOrder::convert(Poco::ByteOrder::fromNetwork, r);
		return vw::LLDate(r).get();
	}
}

namespace vw
{
	String const & LLDate::DateFormat = Poco::DateTimeFormat::ISO8601_FORMAT;

	LLDate::LLDate()
		: m_data(Poco::Timestamp::fromEpochTime(0))
	{		
	}

	LLDate::LLDate(byte_sub_range const & sr)
		: m_data(FromByteSubRange(sr))
	{		
	}

	LLDate::LLDate(Int32 secondsSinceEpoch)
		: m_data(Poco::Timestamp::fromEpochTime(secondsSinceEpoch))
	{		
	}

	LLDate::LLDate(double secondsSinceEpoch)
		: m_data(Poco::Timestamp::fromEpochTime(UInt32(secondsSinceEpoch)))
	{		
	}

	LLDate::LLDate(String const & fromString)
		: m_data(Poco::DateTimeParser::parse(DateFormat, fromString))
	{
	}

	LLDate::LLDate(LLDate const & o)
		: m_data(o.m_data)
	{
	}


	LLDate & LLDate::operator=(LLDate o)
	{
		swap(o);
		return *this;
	}


	bool LLDate::operator == (LLDate const & o) const
	{
		return m_data == o.m_data;
	}
	
	bool LLDate::operator != (LLDate const & o) const
	{
		return m_data != o.m_data;
	}
	
	bool LLDate::operator <  (LLDate const & o) const
	{
		return m_data < o.m_data;
	}
	
	bool LLDate::operator <= (LLDate const & o) const
	{
		return m_data <= o.m_data;
	}
	
	bool LLDate::operator >  (LLDate const & o) const
	{
		return m_data > o.m_data;
	}
	
	bool LLDate::operator >= (LLDate const & o) const
	{
		return m_data >= o.m_data;
	}
	
	void LLDate::swap(LLDate & other)
	{
		m_data.swap(other.m_data);
	}
	
	String LLDate::to_string() const
	{
		using namespace Poco;
		return DateTimeFormatter::format(m_data, DateFormat);
	}

	Int32 LLDate::to_integer() const
	{
		return Int32(m_data.timestamp().epochTime());
	}

	Real64 LLDate::to_real() const
	{
		return Real64(m_data.timestamp().epochTime());
	}

	LLDate::value_type const & LLDate::get() const
	{
		return m_data;
	}

	LLDate::value_type & LLDate::get()
	{
		return m_data;
	}
}

namespace std
{
	istream & operator>>(istream & is, vw::LLDate & d)
	{
		if(Poco::DateTimeParser::tryParseFromStream(vw::LLDate::DateFormat, is, d.get()))
			return is;
		is.setstate(std::ios_base::badbit);
		return is;
	}
}

