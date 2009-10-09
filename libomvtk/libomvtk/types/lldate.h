// vim:et:st=4:ts=4:sts=4:
// Copyright (c) 2008,2009 by the OpenMetaverse Toolkit Library Team
// All rights reserved.
//
// - Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Neither the name of the OpenMetaverse Toolkit Library Team nor the names
//   of its contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE
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
		static String const DateFormat;

		LLDate();
        ~LLDate();
		
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
    ostream & operator<<(ostream & os, omvtk::LLDate const & d);
	istream & operator>>(istream & is, omvtk::LLDate & d);
}

#endif //GUARD_LIBOMVTK_TYPES_LLDATE_H_INCLUDED
