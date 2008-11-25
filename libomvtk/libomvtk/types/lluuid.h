#ifndef GUARD_LIBOMVTK_TYPES_LLUUID_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_LLUUID_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "base_types.h"
#include "sub_range.h"
#include <Poco/UUID.h>

namespace omvtk
{
	struct LLUUID
	{
		/// static zero uuid instance
		static LLUUID const Zero;

		typedef Poco::UUID value_type;

		/// Default constructor initializes Zero LLUUID
		LLUUID();

		/// Initialize from Poco::UUID
		LLUUID(value_type const &);

		/// Initialize from string representation
		LLUUID(String const &);

		/// Initialize the LLUUID from a byte sub range (avoids copies)
		LLUUID(byte_sub_range const &);

		/// Initialize from Buffer
		LLUUID(ByteBuffer const &);		

		/// Copy constructor
		LLUUID(LLUUID const &);

		/// Destructor
		~LLUUID();

		/// Assignment operator
		LLUUID & operator=(LLUUID);

		/// equal compare operator
		bool operator == (const LLUUID& uuid) const;

		/// not equal compare operator 
		bool operator != (const LLUUID& uuid) const;

		/// less than compare operator
		bool operator <  (const LLUUID& uuid) const;

		/// less than or equal compare operator
		bool operator <= (const LLUUID& uuid) const;

		/// greater than compare operator
		bool operator >  (const LLUUID& uuid) const;

		/// greater than or equal compare operator
		bool operator >= (const LLUUID& uuid) const;

		/// Swap implementation
		void swap(LLUUID & other);

		/// Whether the current instance is a zero uuid
		bool is_zero() const;		

		/// Converts to string representation
		String to_string() const;

		/// Converts to binary buffer
		ByteBuffer to_binary() const;		

		/// returns internal Poco::UUID instance
		value_type & get();

		/// returns internal Poco::UUID instance
		value_type const & get() const;
	protected:
		value_type m_data;
	};
}

#include "exceptions.h"

namespace std
{
	inline std::ostream & operator<<(std::ostream & os, omvtk::LLUUID const & v)
	{
		return os << v.to_string();
	}

	inline std::istream & operator>>(std::istream & is, omvtk::LLUUID & v)
	{
		char buffer[37] = {0};
		if(is.read(buffer, 36))
		{
			try
			{
				v = omvtk::LLUUID(buffer);
			}
			catch (omvtk::Exception const &)
			{
				is.setstate(std::ios::badbit);
			}
		}
		return is;
	}
}

#endif //GUARD_LIBOMVTK_TYPES_LLUUID_H_INCLUDED
