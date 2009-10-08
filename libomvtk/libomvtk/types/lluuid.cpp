#include "lluuid.h"
#include "assert.h"
#include <sstream>

namespace // local visibility only so we can use an arbitary name
{
	boost::uuid fromSubRange(omvtk::byte_sub_range const & b)
	{
		boost::uuid uuid;		
		libomvtk_ensure(b.size() == 16);
		uuid.assign(b.begin(), b.end());
		return uuid;
	}

    boost::uuid fromString(omvtk::String const & str)
    {
        std::istringstream istr(str);
        boost::uuid u;
        istr >> u;
        return u;
    }
}

namespace omvtk
{
	/// static zero uuid instance
	LLUUID const LLUUID::Zero = LLUUID();

	/// Default constructor initializes Zero LLUUID
	LLUUID::LLUUID()
		: m_data()
	{		
	}


	/// Initialize from Poco::UUID
	LLUUID::LLUUID(value_type const & val)
		: m_data(val)
	{
	}


	/// Initialize from string representation
	LLUUID::LLUUID(String const & str)
		: m_data(fromString(str))
	{
	}

	/// Initialize the LLUUID from a byte sub range (avoids copies)
	LLUUID::LLUUID(byte_sub_range const & sr)
		: m_data(fromSubRange(sr))
	{

	}

	/// Initialize from Buffer
	LLUUID::LLUUID(ByteBuffer const & buf)
		: m_data(fromSubRange(byte_sub_range(buf.begin(), buf.end())))
	{
	}


	/// Copy constructor
	LLUUID::LLUUID(LLUUID const & other)
		: m_data(other.m_data)
	{
	}


	/// Destructor
	LLUUID::~LLUUID()
	{
	}


	/// Assignment operator
	LLUUID & LLUUID::operator=(LLUUID other)
	{
		swap(other);
		return *this;
	}


	/// equal compare operator
	bool LLUUID::operator == (const LLUUID& uuid) const
	{
		return m_data == uuid.m_data;
	}


	/// not equal compare operator 
	bool LLUUID::operator != (const LLUUID& uuid) const
	{
		return m_data != uuid.m_data;
	}


	/// less than compare operator
	bool LLUUID::operator <  (const LLUUID& uuid) const
	{
		return m_data < uuid.m_data;
	}


	/// less than or equal compare operator
	bool LLUUID::operator <= (const LLUUID& uuid) const
	{
		return m_data <= uuid.m_data;
	}


	/// greater than compare operator
	bool LLUUID::operator >  (const LLUUID& uuid) const
	{
		return m_data > uuid.m_data;
	}


	/// greater than or equal compare operator
	bool LLUUID::operator >= (const LLUUID& uuid) const
	{
		return m_data >= uuid.m_data;
	}

	void LLUUID::swap(LLUUID & other)
	{
		m_data.swap(other.m_data);
	}

	/// Whether the current instance is a zero uuid
	bool LLUUID::is_zero() const
	{
		return m_data.is_nil();
	}


	/// Converts to string representation
	String LLUUID::to_string() const
	{
		std::ostringstream str;
        str << m_data;
        return str.str();
	}


	/// Converts to binary buffer
	ByteBuffer LLUUID::to_binary() const
	{
		return ByteBuffer(m_data.begin(), m_data.end());		
	}


	/// returns internal Poco::UUID instance
	LLUUID::value_type & LLUUID::get()
	{
		return m_data;
	}


	/// returns internal Poco::UUID instance
	LLUUID::value_type const & LLUUID::get() const
	{
		return m_data;
	}

}

