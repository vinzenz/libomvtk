#include "lluuid.h"
#include "assert.h"

namespace // local visibility only so we can use an arbitary name
{
	Poco::UUID fromSubRange(vw::byte_sub_range const & b)
	{
		Poco::UUID uuid;		
		libvw_ensure(b.size() == 16);
		uuid.copyFrom(reinterpret_cast<char const*>(&b[0]));
		return uuid;
	}
}

namespace vw
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
		: m_data(str)
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
		return m_data.isNil();
	}


	/// Converts to string representation
	String LLUUID::to_string() const
	{
		return m_data.toString();
	}


	/// Converts to binary buffer
	ByteBuffer LLUUID::to_binary() const
	{
		ByteBuffer buffer(16,0);
		m_data.copyTo(reinterpret_cast<char*>(&buffer[0]));
		return buffer;
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

