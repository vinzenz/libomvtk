#ifndef GUARD_LIBVW_TYPES_LLURI_H_INCLUDED
#define GUARD_LIBVW_TYPES_LLURI_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "base_types.h"
#include "sub_range.h"
#include <Poco/URI.h>

namespace vw
{
	struct LLURI
	{
		typedef Poco::URI value_type;
		
		/// Create an empty URI
		LLURI();
		
		/// Initialize the LLURI with a Poco::URI object
		LLURI(value_type const &);

		/// Copy constructor
		LLURI(LLURI const &);

		/// Initialize the URI from a \a byte_sub_range
		LLURI(byte_sub_range const &);

		/// Initialize the URI from a string
		LLURI(String const &);

		/// Destructor
		~LLURI();

		/// Assignment operator
		LLURI & operator=(LLURI);

		/// equal compare operator 
		bool operator==(LLURI const &) const;
		/// not equal compare operator 
		bool operator!=(LLURI const &) const;
		/// equal compare operator 
		bool operator==(String const &) const;
		/// not equal compare operator 
		bool operator!=(String const &) const;

		/// Returns the URI as a full string
		String to_string() const;

		/// Returns the URI string in a ByteBuffer object
		ByteBuffer to_binary() const;

		/// swap
		void swap(LLURI & o);

		/// get a reference to the internal Poco::URI object
		value_type const & get() const;
		
		/// get a reference to the internal Poco::URI object
		value_type & get();
	protected:
		value_type m_data;
	};
}

#include "exceptions.h"

namespace std
{
	inline ostream & operator<<(ostream & os, vw::LLURI const & v)
	{
		return os << v.to_string();
	}

	inline istream & operator>>(istream & is, vw::LLURI & v)
	{
		vw::String s;
		if(is >> s)
		{
			try
			{
				v = vw::LLURI(s);
			}
			catch (vw::Exception const &)
			{
				is.setstate(ios_base::badbit);
			}			
		}
		return is;
	}
}

#endif //GUARD_LIBVW_TYPES_LLURI_H_INCLUDED
