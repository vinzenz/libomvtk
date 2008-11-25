#include "stdafx.h"
#include "llsd_integer.h"
#include "llsd_real.h"
#include "llsd_date.h"
#include "llsd_string.h"
#include "llsd_boolean.h"
#include "llsd_binary.h"
#include "byte_order_helper.h"
#include <boost/lexical_cast.hpp>

namespace LLSD
{
	Integer::Integer()
		: Value(VTID_INTEGER)
		, m_value(0)
	{
	}

	Integer::Integer(boost::int32_t value)
		: Value(VTID_INTEGER)
		, m_value(detail::to_network(value))
	{
	}

	Integer::Integer(IntegerPtr const & p)
		: Value(VTID_INTEGER)
		, m_value(p ? p->m_value : 0)
	{
	}

	Integer::Integer(Integer const & o)
		: Value(VTID_INTEGER)
		, m_value(o.m_value)
	{
	}

	Integer::~Integer()
	{
	}

	Integer & Integer::operator=(Integer o)
	{
		m_value = o.m_value;
		return *this;
	}

	IntegerPtr Integer::FromString(std::string const & str)
	{
		return IntegerPtr(new Integer(boost::lexical_cast<boost::int32_t>(str)));
	}

	IntegerPtr Integer::ToInteger() const
	{
		return IntegerPtr(new Integer(*this));
	}

	boost::int32_t Integer::GetValue() const
	{
		return detail::to_host(m_value);
	}

	void Integer::SetValue(boost::uint32_t const & v)
	{
		m_value = detail::to_network(v);
	}

	RealPtr Integer::ToReal() const
	{
		return RealPtr(new Real(double(GetValue())));
	}

	StringPtr Integer::ToString() const
	{
		return StringPtr(new String(boost::lexical_cast<std::string>(GetValue())));
	}

	DatePtr Integer::ToDate() const
	{
		return DatePtr(new Date(GetValue()));
	}

	BooleanPtr Integer::ToBoolean() const
	{
		return BooleanPtr(new Boolean(GetValue() != 0));
	}

	BinaryPtr Integer::ToBinary() const
	{
		boost::uint64_t tmp = detail::to_network(boost::uint64_t(GetValue()));		
		return BinaryPtr(new Binary(reinterpret_cast<boost::uint8_t const *>(&tmp), 8));
	}
}
