#ifndef GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "base_types.h"
#include "sub_range.h"
#include <Poco/DateTime.h>

namespace omvtk
{
	struct LLDate
	{
		typedef Poco::DateTime value_type;
		static String const & DateFormat;

		LLDate();
		
		// the byte sub range represented must be Real64 in network byte order!
		LLDate(byte_sub_range const & sr);
		explicit LLDate(Int32 secondsSinceEpoch);
		explicit LLDate(double secondsSinceEpoch);
		LLDate(String const & fromString);
		LLDate(LLDate const &);

		LLDate & operator=(LLDate);

		bool operator == (LLDate const & dateTime) const;	
		bool operator != (LLDate const & dateTime) const;	
		bool operator <  (LLDate const & dateTime) const;	
		bool operator <= (LLDate const & dateTime) const;	
		bool operator >  (LLDate const & dateTime) const;	
		bool operator >= (LLDate const & dateTime) const;	

		void swap(LLDate & other);
		String to_string() const;	
		Int32 to_integer() const;
		Real64 to_real() const;
		value_type const & get() const;
		value_type & get();
	protected:
		value_type m_data;
	};
}

namespace std
{
	inline ostream & operator<<(ostream & os, omvtk::LLDate const & d)
	{
		return os << d.to_string();
	}

	istream & operator>>(istream & is, omvtk::LLDate & d);
}

#endif //GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED
