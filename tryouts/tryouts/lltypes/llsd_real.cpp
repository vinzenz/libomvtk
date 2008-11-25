#include "stdafx.h"
#include "llsd_real.h"
#include "llsd_integer.h"
#include "llsd_binary.h"
#include "llsd_string.h"
#include "llsd_date.h"
#include "llsd_boolean.h"
#include "byte_order_helper.h"
#include <boost/lexical_cast.hpp>

namespace LLSD
{	
	Real::Real()
		: Value(VTID_REAL)
		, m_value(detail::to_network(0.0))
	{
	}

	Real::Real(double value)
		: Value(VTID_REAL)
		, m_value(detail::to_network(value))
	{
	}

	Real::Real(Real const & o)
		: Value(VTID_REAL)
		, m_value(o.m_value)
	{
	}

	Real::Real(RealPtr const & o)
		: Value(VTID_REAL)
		, m_value(o ? o->m_value : detail::to_network(0.0))
	{
	}

	Real::~Real()
	{
	}


	Real & Real::operator=(Real other)
	{
		m_value = other.m_value;
		return *this;
	}

	RealPtr Real::FromString(std::string const & str)
	{
		double val = std::numeric_limits<double>::quiet_NaN();
		if(str != "nan")
		{
			val = boost::lexical_cast<double>(str);
		}
		return RealPtr(new Real(val));
	}

	double Real::GetValue() const
	{
		return detail::to_host(m_value);
	}

	void Real::SetValue(double value)
	{
		m_value = detail::to_network(value);
	}


	IntegerPtr Real::ToInteger() const
	{
		return IntegerPtr(new Integer(boost::uint32_t(GetValue())));
	}

	RealPtr Real::ToReal() const
	{
		return RealPtr(new Real(*this));
	}

	StringPtr Real::ToString() const
	{
		return StringPtr(new String(boost::lexical_cast<std::string>(GetValue())));
	}

	DatePtr Real::ToDate() const
	{
		return DatePtr(new Date(boost::uint32_t(GetValue())));
	}

	BooleanPtr Real::ToBoolean() const
	{
		return BooleanPtr(new Boolean(GetValue() == 0.0));
	}

	BinaryPtr Real::ToBinary() const
	{
		return BinaryPtr(new Binary(reinterpret_cast<boost::uint8_t const*>(&m_value), 8));
	}

}
