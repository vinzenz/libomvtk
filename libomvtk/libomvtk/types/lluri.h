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
#ifndef GUARD_LIBOMVTK_TYPES_LLURI_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_LLURI_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "base_types.h"
#include "sub_range.h"
#include "uri.h"

namespace omvtk
{
	struct LLURI
	{
		typedef uripp::uri value_type;
		
		/// Create an empty URI
		LLURI();
		
		/// Copy constructor
		LLURI(LLURI const &);

		/// Initialize the URI from a \a byte_sub_range
		LLURI(byte_sub_range const &);

		/// Initialize the URI from a string
		LLURI(String const &);

		/// Initialize the URI from a value_type
		LLURI(value_type const &);

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

		/// get a reference to the internal object
		value_type const & get() const;
		
		/// get a reference to the internal object
		value_type & get();
	protected:
		value_type m_data;
	};
}

#include "exceptions.h"

namespace std
{
	inline ostream & operator<<(ostream & os, omvtk::LLURI const & v)
	{
		return os << v.to_string();
	}

	inline istream & operator>>(istream & is, omvtk::LLURI & v)
	{
		omvtk::String s;
		if(is >> s)
		{
			try
			{
				v = omvtk::LLURI(s);
			}
			catch (omvtk::Exception const &)
			{
				is.setstate(ios_base::badbit);
			}			
		}
		return is;
	}
}

#endif //GUARD_LIBOMVTK_TYPES_LLURI_H_INCLUDED
