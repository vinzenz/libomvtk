#include "stdafx.h"
#include "llsd_binary.h"
#include "llsd_string.h"
#include "llsd_real.h"
#include "llsd_integer.h"
#include "llsd_boolean.h"
#include "llsd_uri.h"
#include "llsd_uuid.h"

namespace LLSD
{
	Uri::Uri()
		: Value(VTID_URI)
		, m_value()
	{
	}

	Uri::Uri(Poco::URI const & uri)
		: Value(VTID_URI)
		, m_value(uri)
	{
	}

	Uri::Uri(std::string const & uri)
		: Value(VTID_URI)
		, m_value(uri)
	{
	}

	Uri::Uri(Uri const & o)
		: Value(VTID_URI)
		, m_value(o.m_value)
	{
	}

	Uri::Uri(UriPtr const & p)
		: Value(VTID_URI)
		, m_value(p ? p->m_value : Poco::URI())
	{
	}

	Uri::~Uri()
	{
	}

	Uri & Uri::operator=(Uri o)
	{
		o.m_value.swap(o.m_value);
		return *this;
	}

	Poco::URI const & Uri::GetValue()
	{
		return m_value;
	}

	void Uri::SetValue(Poco::URI const & value)
	{
		m_value = value;
	}

	StringPtr Uri::ToString() const
	{
		return StringPtr(new String(m_value.toString()));
	}

	UriPtr Uri::ToUri() const
	{
		return UriPtr(new Uri(*this));
	}
}