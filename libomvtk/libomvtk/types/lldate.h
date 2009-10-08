#ifndef GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "base_types.h"
#include "sub_range.h"
#include <boost/date_time/posix_time/posix_time.hpp>


namespace omvtk
{
    struct LLDate_P;
	struct LLDate
	{
		typedef boost::posix_time::ptime value_type;
		static String const & DateFormat;

		LLDate();
        ~LLDate();
		
		// the byte sub range represented must be Real64 in network byte order!
		LLDate(byte_sub_range const & sr);
		explicit LLDate(Int32 secondsSinceEpoch);
		explicit LLDate(double secondsSinceEpoch);
		LLDate(String const & fromString);
		LLDate(LLDate const &);

		LLDate & operator=(const LLDate & );

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
        LLDate_P * d;
	};
}

namespace std
{
    ostream & operator<<(ostream & os, omvtk::LLDate const & d);
	istream & operator>>(istream & is, omvtk::LLDate & d);
}

#endif //GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED
