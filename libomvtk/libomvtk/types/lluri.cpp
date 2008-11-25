#include "lluri.h"

namespace omvtk
{
	LLURI::LLURI()
	{
	}

	LLURI::LLURI(value_type const & v)
		: m_data(v)
	{
	}

	LLURI::LLURI(LLURI const & o)
		: m_data(o.m_data)
	{
	}

	LLURI::LLURI(byte_sub_range const & sr)
		: m_data(String(sr.begin(), sr.end()))
	{
	}

	LLURI::LLURI(String const & str)
		: m_data(str)
	{
	}

	LLURI::~LLURI()
	{
	}

	LLURI & LLURI::operator=(LLURI o)
	{
		swap(o);
		return *this;
	}


	bool LLURI::operator==(LLURI const & o) const
	{
		return m_data == o.m_data;
	}

	bool LLURI::operator!=(LLURI const & o) const
	{
		return m_data != o.m_data;
	}

	bool LLURI::operator==(String const & s) const
	{
		return m_data == s;
	}

	bool LLURI::operator!=(String const & s) const
	{
		return m_data != s;
	}
	
	void LLURI::swap(LLURI & o)
	{
		m_data.swap(o.m_data);
	}

	String LLURI::to_string() const
	{
		return m_data.toString();
	}

	ByteBuffer LLURI::to_binary() const
	{
		std::string tmp = to_string();
		return ByteBuffer(tmp.begin(), tmp.end());
	}


	LLURI::value_type const & LLURI::get() const
	{
		return m_data;
	}

	LLURI::value_type & LLURI::get()
	{
		return m_data;
	}

}

