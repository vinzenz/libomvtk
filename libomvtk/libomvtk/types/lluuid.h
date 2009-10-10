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
#ifndef GUARD_LIBOMVTK_TYPES_LLUUID_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_LLUUID_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "base_types.h"
#include "sub_range.h"
#include <boost/uuid.hpp>

namespace omvtk
{
	struct LLUUID
	{
		/// static zero uuid instance
		static LLUUID const Zero;

		typedef boost::uuid value_type;

		/// Default constructor initializes Zero LLUUID
		LLUUID();

		/// Initialize from an internal value_type object 
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

		/// returns the internal instance
		value_type & get();

		/// returns the internal instance
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
