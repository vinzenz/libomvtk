#include "stdafx.h"
#include "llsd_binary.h"
#include "llsd_boolean.h"
#include "llsd_real.h"
#include "llsd_string.h"
#include "llsd_integer.h"
#include "llsd_uuid.h"
#include "llsd_uri.h"
#include "byte_order_helper.h"
#include "../base64.h"

namespace LLSD
{
	Binary::Binary()
		: Value(VTID_BINARY)
		, m_value()
	{
	}

	Binary::Binary(boost::uint8_t const * buffer, size_t buffer_size)
		: Value(VTID_BINARY)
		, m_value(buffer,buffer+buffer_size)
	{
	}

	Binary::Binary(Container const & buf)
		: Value(VTID_BINARY)
		, m_value(buf)
	{
	}

	Binary::Binary(Binary const & o)
		: Value(VTID_BINARY)
		, m_value(o.m_value)
	{
	}

	Binary::Binary(BinaryPtr const & p)
		: Value(VTID_BINARY)
		, m_value(p ? p->m_value : Container())
	{
	}

	Binary::~Binary()
	{
	}

	Binary & Binary::operator=(Binary o)
	{
		m_value.swap(o.m_value);
		return *this;
	}

	BinaryPtr Binary::FromBase64(std::string const & str)
	{
		return BinaryPtr(new Binary(encoding::base64_decode<Container>(str)));
	}

	BinaryPtr Binary::FromBase64(std::wstring const & str)
	{
		return BinaryPtr(new Binary(encoding::base64_decode<Container>(str)));
	}

	std::string Binary::ToBase64()
	{
		return encoding::base64_encode<std::string>(m_value);
	}

	Binary::Container const & Binary::GetValue() const
	{
		return m_value;
	}

	void Binary::SetValue(Container const & o)
	{
		m_value = o;
	}

	void Binary::SetValue(boost::uint8_t const * buffer, size_t buffer_size)
	{
		m_value.assign(buffer, buffer+buffer_size);
	}

	IntegerPtr Binary::ToInteger() const
	{
		boost::uint64_t val = 0;
		if(m_value.size() == 8)
		{
			val = *reinterpret_cast<boost::uint8_t const*>(&m_value[0]);
			val = detail::to_host(val);
		}
		return IntegerPtr(new Integer(boost::int32_t(val)));
	}

	RealPtr Binary::ToReal() const
	{
		double val = 0;
		if(m_value.size() == 8)
		{
			val = *reinterpret_cast<double const*>(&m_value[0]);
			val = detail::to_host(val);
		}
		return RealPtr(new Real(val));
	}

	StringPtr Binary::ToString() const
	{
		return StringPtr(new String(std::string(m_value.begin(), m_value.end())));
	}

	UUIDPtr Binary::ToUUID() const
	{
		if(m_value.size() == 16)
			return UUIDPtr(new UUID(m_value));
		return UUIDPtr(new UUID());
	}

	BooleanPtr Binary::ToBoolean() const
	{
		return BooleanPtr(new Boolean(!m_value.empty()));
	}

	BinaryPtr Binary::ToBinary() const
	{
		return BinaryPtr(new Binary(*this));
	}

	UriPtr Binary::ToUri() const
	{
		return UriPtr(new Uri(std::string(m_value.begin(), m_value.end())));
	}
}