#include "StdAfx.h"
#include "llsd_boolean.h"
#include "llsd_integer.h"
#include "llsd_string.h"
#include "llsd_date.h"
#include "llsd_real.h"
#include "llsd_binary.h"

namespace LLSD
{
	Boolean::Boolean()
		: Value(VTID_BOOLEAN)
		, m_value(false)
	{
	}

	Boolean::Boolean(bool value)
		: Value(VTID_BOOLEAN)
		, m_value(value)
	{
	}

	Boolean::Boolean(Boolean const & o)
		: Value(VTID_BOOLEAN)
		, m_value(o.m_value)
	{
	}

	Boolean::Boolean(BooleanPtr const & o)
		: Value(VTID_BOOLEAN)
		, m_value(o ? o->m_value : false)
	{
	}


	Boolean::~Boolean()
	{
	}

	Boolean & Boolean::operator=(Boolean o)
	{
		m_value = o.m_value;
		return *this;
	}


	bool Boolean::GetValue() const
	{
		return m_value;
	}

	void Boolean::SetValue(bool value)
	{
		m_value = value;
	}


	IntegerPtr Boolean::ToInteger() const
	{
		return IntegerPtr(new Integer(m_value ? 1 : 0));
	}

	RealPtr Boolean::ToReal() const
	{
		return RealPtr(new Real(m_value ? 1.0 : 0.0));
	}

	StringPtr Boolean::ToString() const
	{
		return StringPtr(new String(m_value ? "true" : "false"));
	}

	BooleanPtr Boolean::ToBoolean() const
	{
		return BooleanPtr(new Boolean(*this));
	}

	BinaryPtr Boolean::ToBinary() const
	{
		char tmp = m_value ? '1' : '0';
		return BinaryPtr(new Binary(reinterpret_cast<boost::uint8_t const *>(&tmp), 1));
	}
}

