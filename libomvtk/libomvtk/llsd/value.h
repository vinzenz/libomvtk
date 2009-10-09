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
#ifndef GUARD_LIBOMVTK_LLSD_LLSD_VALUE_H_INCLUDED
#define GUARD_LIBOMVTK_LLSD_LLSD_VALUE_H_INCLUDED

#if _MSC_VER > 1200
#	pragma once
#endif

#include "../types/base_types.h"
#include "../types/lluri.h"
#include "../types/lluuid.h"
#include "../types/lldate.h"

#include <map>
#include <vector>
#include <boost/any.hpp>

namespace omvtk
{
	struct LLSDValue
	{		
		enum Types
		{
			VT_UNDEF,
			VT_BOOLEAN,
			VT_INTEGER,
			VT_REAL,
			VT_STRING,
			VT_UUID,
			VT_URI,
			VT_DATE,
			VT_BINARY,
			VT_ARRAY,
			VT_MAP
		};
		struct Undef{};
		typedef bool						Boolean;
		typedef Int32						Integer;
		typedef Real64						Real;
		typedef omvtk::String					String;
		typedef LLURI						URI;
		typedef LLUUID						UUID;
		typedef LLDate						Date;
		typedef ByteBuffer					Binary;
		typedef std::map<String,LLSDValue>  Map;
		typedef std::vector<LLSDValue>		Array;
		
		/// Default constructor initializes with VT_UNDEF 
		LLSDValue();
		/// Copy constructor
		LLSDValue(LLSDValue const &);
		/// Constructing from Boolean
		LLSDValue(Boolean v);
		/// Constructing from Integer
		LLSDValue(Integer v);
		/// Constructing from Real64
		LLSDValue(Real v);
		/// Constructing from String
		LLSDValue(String const & v);
		/// Constructing from String
		LLSDValue(char const * v);
		/// Constructing from URI
		LLSDValue(URI const & v);
		/// Constructing from UUID
		LLSDValue(UUID const & v);
		/// Constructing from Date
		LLSDValue(Date const & v);
		/// Constructing from Binary
		LLSDValue(Binary const & v);		
		/// Constructing from Map
		LLSDValue(Map const & v);	
		/// Constructing from Array
		LLSDValue(Array const & v);
		/// Constructing from Undef
		LLSDValue(Undef const &);

		/// Assignment operator LLSDValue
		LLSDValue & operator=(LLSDValue);
		/// Assignment operator for Boolean
		LLSDValue & operator=(Boolean v);
		/// Assignment operator for Integer
		LLSDValue & operator=(Integer v);
		/// Assignment operator for Real64
		LLSDValue & operator=(Real v);
		/// Assignment operator for String
		LLSDValue & operator=(String const & v);
		/// Assignment operator for String
		LLSDValue & operator=(char const * v);
		/// Assignment operator for URI
		LLSDValue & operator=(URI const & v);
		/// Assignment operator for UUID
		LLSDValue & operator=(UUID const & v);
		/// Assignment operator for Date
		LLSDValue & operator=(Date const & v);
		/// Assignment operator for Binary
		LLSDValue & operator=(Binary const & v);
		/// Assignment operator for Map
		LLSDValue & operator=(Map const & v);
		/// Assignment operator for Array
		LLSDValue & operator=(Array const & v);
		/// Assigment of undef
		LLSDValue & operator=(Undef const &);

		/// return true if the underlying value is not VT_UNDEF
		/// otherwise it returns false
		operator bool() const;
		/// compares two LLSDValue objects for equality
		bool operator == (LLSDValue const & value) const;
		/// compares two LLSDValue objects for non-equality
		bool operator != (LLSDValue const & value) const;

		/// Conversion method forces conversion to Boolean
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		Boolean to_boolean() const;

		/// Conversion method forces conversion to Integer
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		Integer to_integer() const;

		/// Conversion method forces conversion to Real
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		Real	to_real()	 const;

		/// Conversion method forces conversion to String
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		String	to_string()	 const;

		/// Conversion method forces conversion to UUID
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		UUID	to_uuid()	 const;

		/// Conversion method forces conversion to URI
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		URI		to_uri()	 const;

		/// Conversion method forces conversion to Date
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		Date	to_date()	 const;

		/// Conversion method forces conversion to Binary
		/// those will throw std::exception based exceptions on errors
		/// omvtk::BadCastException if it is not implemented for the type
		/// boost::bad_lexical_cast if a lexical conversion failed		
		Binary	to_binary()  const;

		// Returns the VT_ type of the underlying value
		Types type() const;
		// Swaps content
		void swap(LLSDValue & other);
		// clears the value to undefined
		void clear(); 

		/// Access boolean value beneath
		/// Remark: It will throw an exception if it is not VT_BOOLEAN 
		Boolean const & boolean() const;
		/// Access boolean value beneath
		/// Remark: It will throw an exception if it is not VT_BOOLEAN 
		Boolean & boolean();

		/// Access integer value beneath
		/// Remark: It will throw an exception if it is not VT_INTEGER 
		Integer const & integer() const;
		/// Access integer value beneath
		/// Remark: It will throw an exception if it is not VT_INTEGER 
		Integer & integer();

		/// Access real64 value beneath
		/// Remark: It will throw an exception if it is not VT_REAL 
		Real	const & real() const;
		/// Access real64 value beneath
		/// Remark: It will throw an exception if it is not VT_REAL
		Real	& real();

		/// Access string value beneath
		/// Remark: It will throw an exception if it is not VT_STRING
		String	const & string() const;
		/// Access string value beneath
		/// Remark: It will throw an exception if it is not VT_STRING
		String	& string();

		/// Access LLUUID value beneath
		/// Remark: It will throw an exception if it is not VT_UUID
		UUID	const & uuid() const;
		/// Access LLUUID value beneath
		/// Remark: It will throw an exception if it is not VT_UUID
		UUID	& uuid();

		/// Access LLURI value beneath
		/// Remark: It will throw an exception if it is not VT_URI
		URI		const & uri() const;
		/// Access LLURI value beneath
		/// Remark: It will throw an exception if it is not VT_URI
		URI		& uri();

		/// Access LLDate value beneath
		/// Remark: It will throw an exception if it is not VT_DATE
		Date	const & date() const;
		/// Access LLDate value beneath
		/// Remark: It will throw an exception if it is not VT_DATE
		Date	& date();

		/// Access Binary value beneath
		/// Remark: It will throw an exception if it is not VT_BINARY
		Binary	const & binary() const;
		/// Access Binary value beneath
		/// Remark: It will throw an exception if it is not VT_BINARY
		Binary	& binary();

		/// Access Array value beneath
		/// Remark: It will throw an exception if it is not VT_ARRAY
		Array	const & array() const;
		/// Access Array value beneath
		/// Remark: It will throw an exception if it is not VT_ARRAY
		Array	& array();

		/// Access Map value beneath
		/// Remark: It will throw an exception if it is not VT_MAP
		Map		const & map() const;
		/// Access Map value beneath
		/// Remark: It will throw an exception if it is not VT_MAP
		Map		& map();

		/// Encodes value as LLSD+XML
		String xml_encode() const;
		/// Encodes value as LLSD+Notation
		String notation_encode() const;
		/// Encodes value as LLSD+Binary
		void binary_encode(Binary & out) const;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
		/// Helper function for the decoder, should not be used to parse
		/// LLSD+XML directly
		void xml_decode(Types typeID, byte_sub_range const &);
		/// Helper function for the decoder, should not be used to parse
		/// LLSD+Notation directly
		void notation_decode(Types typeID, byte_sub_range const &);
		/// Helper function for the decoder, should not be used to parse
		/// LLSD+Binary directly
		void binary_decode(Types typeID, byte_sub_range const &);

		/// Helper function for the decoder, should not be used to parse
		/// LLSD+XML directly
		template<typename Iterator>
		void xml_decode(Types typeID, Iterator it, Iterator end)
		{
			return xml_decode(typeID, byte_sub_range(it,end));
		}

		/// Helper function for the decoder, should not be used to parse
		/// LLSD+XML directly
		template<typename ContainerT>
		void xml_decode(Types typeID, ContainerT const & cont)
		{
			return xml_decode(typeID, byte_sub_range(cont.begin(),cont.end()));
		}

		/// Helper function for the decoder, should not be used to parse
		/// LLSD+Notation directly
		template<typename Iterator>
		void notation_decode(Types typeID, Iterator it, Iterator end)
		{
			return notation_decode(typeID, byte_sub_range(it,end));
		}

		/// Helper function for the decoder, should not be used to parse
		/// LLSD+Binary directly
		template<typename Iterator>
		void binary_decode(Types typeID, Iterator it, Iterator end)
		{
			binary_decode(typeID, byte_sub_range(it,end));
		}
#endif
	protected:
		boost::any m_value;
		Types m_current;
	};
}

#endif //GUARD_LIBOMVTK_LLSD_LLSD_VALUE_H_INCLUDED
