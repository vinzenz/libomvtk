#include "stdafx.h"
#include "llsd_date.h"
#include "llsd_integer.h"
#include "llsd_string.h"
#include "llsd_real.h"
#include "../throw.h"
#include <boost/date_time/posix_time/time_serialize.hpp>

namespace LLSD
{
	Date::Date()
		: Value(VTID_DATE)
		, m_value()
	{
	}

	Date::Date(boost::int32_t secsSinceEpoch)
		: Value(VTID_DATE)
		, m_value(boost::posix_time::from_time_t(std::time_t(secsSinceEpoch)))
	{
	}

	Date::Date(Date const & o)
		: Value(VTID_DATE)
		, m_value(o.m_value)
	{
	}

	Date::Date(DatePtr const & p)
		: Value(VTID_DATE)
		, m_value(p ? p->m_value : boost::posix_time::ptime())
	{
	}

	Date::Date(boost::posix_time::ptime const & p)
		: Value(VTID_DATE)
		, m_value(p)
	{
	}

	Date::~Date()
	{
	}


	Date & Date::operator=(Date d)
	{
		std::swap(d.m_value, m_value);
		return *this;
	}

	DatePtr Date::CreateFromISOString(std::string const & str)
	{
		std::string::const_iterator e = std::find(str.begin(), str.end(),'Z');
		return DatePtr(new Date(boost::date_time::parse_delimited_time<boost::posix_time::ptime>(std::string(str.begin(), e), 'T')));
	}

	std::string Date::MakeIso(DatePtr const & ptr)
	{
		if(!ptr)
			LIBVW_THROWS(InvalidArgumentException);
		return MakeIso(*ptr);
	}

	std::string Date::MakeIso(Date const & ptr)
	{
		return boost::posix_time::to_iso_extended_string(ptr.GetValue()) + "Z";
	}

	boost::posix_time::ptime const & Date::GetValue() const
	{
		return m_value;
	}

	void Date::SetValue(boost::posix_time::ptime const & value)
	{
		m_value = value;
	}


	IntegerPtr Date::ToInteger() const
	{
		return IntegerPtr(new Integer(GetSeconds()));
	}

	RealPtr Date::ToReal() const
	{
		return RealPtr(new Real(double(GetSeconds())));
	}

	StringPtr Date::ToString() const
	{
		return StringPtr(new String(MakeIso(*this)));
	}

	DatePtr Date::ToDate() const
	{
		return DatePtr(new Date(*this));
	}

	boost::uint32_t Date::GetSeconds() const
	{
		if(!m_value.is_not_a_date_time())
		{
			static boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
			boost::posix_time::time_duration diff = m_value - epoch;
			return diff.total_seconds();
		}
		return 0;
	}

}