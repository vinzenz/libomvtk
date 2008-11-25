#include "stdafx.h"
#include "llsd_uuid.h"
#include "llsd_boolean.h"
#include "llsd_string.h"
#include "llsd_binary.h"
#include <cctype>
#include <sstream>
#include <iomanip>
#include <Poco/Exception.h>

namespace
{
	bool isHex(char c)
	{
	//	c = std::tolower(c);
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'));
	}
}

namespace LLSD
{
	UUID UUID::Zero = UUID();

	UUID::UUID()
		: Value(VTID_UUID)
		, m_value()
	{
	}

	UUID::UUID(std::string const & val)
		: Value(VTID_UUID)
		, m_value(val)
	{
	}

	UUID::UUID(value_type const & r)
		: Value(VTID_UUID)
		, m_value(r)
	{
	}

	UUID::UUID(std::vector<boost::uint8_t> const & r)
		: Value(VTID_UUID)
		, m_value()
	{
		if(r.size() == 16)
			m_value.copyFrom(reinterpret_cast<char const*>(&r[0]));
		else
			throw Poco::InvalidArgumentException(__FILE__);
	}

	UUID::UUID(UUID const & o)
		: Value(VTID_UUID)
		, m_value(o.m_value)
	{
	}

	UUID::UUID(UUIDPtr const & p)
		: Value(VTID_UUID)
		, m_value(p ? p->m_value : value_type())
	{
	}

	UUID::~UUID()
	{
	}

	bool UUID::IsZero() const
	{
		return m_value.isNil();
	}
	
	UUID::value_type UUID::ToRaw(std::string const & val)
	{
		return UUID(val).GetValue();		
	}

	std::string UUID::ToString(UUID const & u)
	{
		return u.m_value.toString();
	}

	UUID::value_type const & UUID::GetValue() const
	{
		return m_value;
	}

	void UUID::SetValue(value_type const & r)
	{
		m_value = r;
	}

	void UUID::SetValue(std::vector<boost::uint8_t> const & buf)
	{		
		UUID(buf).m_value.swap(m_value);		
	}

	void UUID::SetValue(std::string const & value)
	{
		m_value = ToRaw(value);
	}

	StringPtr UUID::ToString() const
	{
		return StringPtr(new String(ToString(*this)));
	}

	UUIDPtr UUID::ToUUID() const
	{
		return UUIDPtr(new UUID(*this));
	}

	BooleanPtr UUID::ToBoolean() const
	{
		return BooleanPtr(new Boolean(IsZero()));
	}

	BinaryPtr UUID::ToBinary() const
	{
		std::vector<char> bytes(16,0);
		m_value.copyTo(&bytes[0]);
		return BinaryPtr(new Binary(bytes.begin(), bytes.end()));
	}
}