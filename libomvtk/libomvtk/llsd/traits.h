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
#ifndef GUARD_LIBOMVTK_LLSD_LLSD_TRAITS_H_INCLUDED
#define GUARD_LIBOMVTK_LLSD_LLSD_TRAITS_H_INCLUDED
#ifndef DOXYGEN_SHOULD_SKIP_THIS

#if _MSC_VER > 1200
#	pragma once
#endif

#define TIXML_USE_STL
#include "../../3rdparty/tinyxml/tinyxml.h"
#include "value.h"
#include "../types/assert.h"
#include "../types/exceptions.h"
#include "../types/byte_order.h"

#include <sstream>

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/any.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

namespace omvtk
{
	namespace detail
	{
		template<LLSDValue::Types TypeID>
		struct LLSDTraits;

		template<typename InputContainerType>
		inline String base64_encode(InputContainerType const & cont)
		{
			using namespace boost::archive::iterators;
			typedef base64_from_binary<
				transform_width<
				typename InputContainerType::const_pointer, 6, 8, boost::uint8_t
				>
			> base64_t;
			return String(base64_t(&cont[0]), base64_t(&cont[0] + cont.size()));
		}
		
		template<typename Container, typename CharT>
		inline Container base64_decode(std::basic_string<CharT> str)
		{
			str.append(str.size() % 4, CharT('='));
			typedef boost::archive::iterators::transform_width<
				boost::archive::iterators::binary_from_base64<CharT *>, 8, 6, boost::uint8_t
			> binary_t;

			typename std::basic_string<CharT>::size_type pos = str.find_last_not_of(CharT('='));		
			// calculate how many characters we need to process		
			pos = (pos == str.size() -1 ? str.size() : pos );		
			return Container(binary_t(&str[0]), binary_t(&str[0] + pos));
		}

		inline String escape_string(String const & str)
		{
			static String::value_type const * EncodingChars[256] =
			{
				"\\x00","\\x01","\\x02","\\x03","\\x04",
				"\\x05","\\x06","\\a","\\b","\\t","\\n",
				"\\v","\\f","\\r","\\x0e","\\x0f","\\x10",
				"\\x11","\\x12","\\x13","\\x14","\\x15",
				"\\x16","\\x17","\\x18","\\x19","\\x1a",
				"\\x1b","\\x1c","\\x1d","\\x1e","\\x1f",
				" ","!","\"","#","$","%","&","\\'","(",
				")","*","+",",","-",".","/","0","1","2",
				"3","4","5","6","7","8","9",":",";","<",
				"=",">","?","@","A","B","C","D","E","F",
				"G","H","I","J","K","L","M","N","O","P",
				"Q","R","S","T","U","V","W","X","Y","Z",
				"[","\\\\","]","^","_","`","a","b","c",
				"d","e","f","g","h","i","j","k","l","m",
				"n","o","p","q","r","s","t","u","v","w",
				"x","y","z","{","|","}","~","\\x7f","\\x80",
				"\\x81","\\x82","\\x83","\\x84","\\x85",
				"\\x86","\\x87","\\x88","\\x89","\\x8a",
				"\\x8b","\\x8c","\\x8d","\\x8e","\\x8f",
				"\\x90","\\x91","\\x92","\\x93","\\x94",
				"\\x95","\\x96","\\x97","\\x98","\\x99",
				"\\x9a","\\x9b","\\x9c","\\x9d","\\x9e",
				"\\x9f","\\xa0","\\xa1","\\xa2","\\xa3",
				"\\xa4","\\xa5","\\xa6","\\xa7","\\xa8",
				"\\xa9","\\xaa","\\xab","\\xac","\\xad",
				"\\xae","\\xaf","\\xb0","\\xb1","\\xb2",
				"\\xb3","\\xb4","\\xb5","\\xb6","\\xb7",
				"\\xb8","\\xb9","\\xba","\\xbb","\\xbc",
				"\\xbd","\\xbe","\\xbf","\\xc0","\\xc1",
				"\\xc2","\\xc3","\\xc4","\\xc5","\\xc6",
				"\\xc7","\\xc8","\\xc9","\\xca","\\xcb",
				"\\xcc","\\xcd","\\xce","\\xcf","\\xd0",
				"\\xd1","\\xd2","\\xd3","\\xd4","\\xd5",
				"\\xd6","\\xd7","\\xd8","\\xd9","\\xda",
				"\\xdb","\\xdc","\\xdd","\\xde","\\xdf",
				"\\xe0","\\xe1","\\xe2","\\xe3","\\xe4",
				"\\xe5","\\xe6","\\xe7","\\xe8","\\xe9",
				"\\xea","\\xeb","\\xec","\\xed","\\xee",
				"\\xef","\\xf0","\\xf1","\\xf2","\\xf3",
				"\\xf4","\\xf5","\\xf6","\\xf7","\\xf8",
				"\\xf9","\\xfa","\\xfb","\\xfc","\\xfd",
				"\\xfe","\\xff"		
			};
			String ret;
			BOOST_FOREACH(String::value_type c, str)
			{
				ret += EncodingChars[UInt16(c)];
			}
			return ret;
		}


		//	VT_STRING,
		//	Conversion type	rules	
		//	boolean	empty => false, all other values => true	
		//	integer	A simple conversion of the initial characters to an integer	
		//	real	A simple conversion of the initial characters to a real number	
		//	uuid	A valid 8-4-4-4-12 is converted to a uuid, all other values => null uuid	
		//	string	unity	
		//	binary	raw representation of the characters	
		//	date	An interpretation of the string as a date	
		//	uri	An interpretation of the string as a link
		template<>
		struct LLSDTraits<LLSDValue::VT_STRING>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_STRING);
			typedef LLSDValue::String Type;

			static inline void convert(LLSDValue::Boolean & to, Type const & from)
			{
				to = !from.empty();
			}
			static inline void convert(LLSDValue::Integer & to, Type const & from)
			{
				to = boost::lexical_cast<LLSDValue::Integer>(from);
			}
			static inline void convert(LLSDValue::Real & to, Type const & from)	
			{
				if(from == "nan")
				{
					to = std::numeric_limits<LLSDValue::Real>::quiet_NaN();
				}
				else
				{
					to = boost::lexical_cast<LLSDValue::Real>(from);
				}				
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to.assign(from);
			}
			static inline void convert(LLSDValue::Binary & to, Type const & from)
			{
				to.assign(from.begin(), from.end());
			}
			static inline void convert(LLSDValue::Date & to, Type const & from)
			{
				LLSDValue::Date fromDate(from);
				to.swap(fromDate);
			}
			static inline void convert(LLSDValue::URI & to, Type const & from)
			{
				to = from;
			}
			static inline void convert(LLSDValue::UUID & to, Type const & from)
			{
				LLSDValue::UUID fromUUID(from);
				to.swap(fromUUID);
			}

			static inline String xml_encode(Type const & value)
			{
				Type tmp;
				TiXmlBase::EncodeString(value, &tmp);
				return "<string>" + tmp + "</string>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{				
				return Type(iter, end);
			}

			static inline String notation_encode(Type const & value)
			{
				return "'"  + escape_string(value) + "'";
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				return Type(iter,end);
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & type)
			{
				UInt32 tmp = to_network(UInt32(type.size()));
				Byte const * p  = reinterpret_cast<Byte const*>(&tmp);
				out.push_back('s');
				out.insert(out.end(), p, p + sizeof(UInt32));
				out.insert(out.end(), type.begin(), type.end());
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				return Type(iter, end);
			}
		};

		// Conversion type	rules	
		// boolean	unity	
		// integer	true => 1, false => 0	
		// real	true => 1.0, false => 0.0	
		// uuid	n/a	
		// string	'true', 'false'	
		// binary	one byte us-ascii where true => 1, false => 0	
		// date	n/a	
		// uri	n/a
		template<>
		struct LLSDTraits<LLSDValue::VT_BOOLEAN>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_BOOLEAN);
			typedef LLSDValue::Boolean Type;

			static inline void convert(LLSDValue::Boolean & to, Type const & from)
			{
				to = from;
			}
			static inline void convert(LLSDValue::Integer & to, Type const & from)
			{
				to = LLSDValue::Integer(from);
			}
			static inline void convert(LLSDValue::Real & to, Type const & from)	
			{
				to = from ? 1.0 : 0.0;
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to = from ? "true" : "false";
			}
			static inline void convert(LLSDValue::Binary & to, Type const & from)
			{
				to.clear();
				to.push_back(from ? Byte('1') : Byte('0'));
			}
			static inline void convert(LLSDValue::Date &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Boolean to Date");
			}
			static inline void convert(LLSDValue::URI &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Boolean to LLURI");
			}
			static inline void convert(LLSDValue::UUID &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Boolean to LLUUID");
			}

			static inline String xml_encode(Type const & value)
			{
				return "<boolean>" + String(value ? "1" : "0") + "</boolean>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				String s(iter, end);
				libomvtk_ensure(s.size() >= 1);
				if(s == "true" || s == "1")
					return Type(true);
				else if(s == "false" || s == "0")
					return Type(false);
				else if(iter == end)
					return Type(false);
				boost::throw_exception(SyntaxException("LLSD XML Parser error"));
				return Type();
			}

			static inline String notation_encode(Type const & value)
			{
				return value ? "1" : "0";
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				String s(iter, end);
				boost::algorithm::to_lower(s);
				if(s == "1" || s == "t" || s == "true")
					return Type(true);
				if(s == "0" || s == "f" || s == "false")
					return Type(false);
				boost::throw_exception(SyntaxException("LLSD Notation Parser error"));
				return Type();
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & type)
			{
				out.push_back(Byte(type ? '1' : '0'));
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				byte_sub_range sr(iter, end);
				return Type();
			}
		};

		//	VT_BINARY,
		//	Conversion type	rules	
		//	boolean	empty => false, all other values => true	
		//	integer	len < 4 => 0, otherwise first four bytes are interpreted as a network byte order integer	
		//	real	len < 8 => 0, otherwise first eight bytes are interpreted as a network byte order double	
		//	uuid	len < 16 => null uuid, otherwise first sixteen bytes are interpreted as the raw binary uuid	
		//	string	the raw binary data interpreted as utf-8 character data	
		//	binary	unity	
		//	date	n/a	
		//	uri	the raw binary data interpreted as a utf-8 serialized link
		template<>
		struct LLSDTraits<LLSDValue::VT_BINARY>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_BINARY);
			typedef LLSDValue::Binary Type;

			static inline void convert(LLSDValue::Boolean & to, Type const & from)
			{
				to = !from.empty();
			}
			static inline void convert(LLSDValue::Integer & to, Type const & from)
			{
				typedef LLSDValue::Integer TargetT;
				if(from.size() < sizeof(TargetT))
					to = 0;
				else
					to = to_host(*reinterpret_cast<TargetT const *>(&from[0]));
			}
			static inline void convert(LLSDValue::Real & to, Type const & from)	
			{
				typedef LLSDValue::Real TargetT;
				if(from.size() < sizeof(TargetT))
					to = 0;
				else
					to = to_host(*reinterpret_cast<TargetT const *>(&from[0]));
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to.assign(from.begin(), from.end());
			}
			static inline void convert(LLSDValue::Binary & to, Type const & from)
			{
				to = from;
			}
			static inline void convert(LLSDValue::Date &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from UUID to Date");
			}
			static inline void convert(LLSDValue::URI & to, Type const & from)
			{
				to = LLSDValue::URI(byte_sub_range(from.begin(), from.end()));
			}
			static inline void convert(LLSDValue::UUID & to, Type const & from)
			{
				if(from.size() < 16)
					to = LLSDValue::UUID();
				else
					to = LLSDValue::UUID(byte_sub_range(from.begin(), from.begin() + 16));
			}

			static inline String xml_encode(Type const & value)
			{
				return "<binary encoding=\"base64\">" + base64_encode(value) + "</binary>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				return Type(iter,end);
			}

			static inline String notation_encode(Type const & value)
			{
				return "b64\"" + base64_encode(value) + "\"";
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				return Type(iter,end);
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				UInt32 size = to_network(UInt32(value.size()));
				Byte * p = reinterpret_cast<Byte*>(&size);
				out.push_back(Byte('b'));
				out.insert(out.end(), p, p+sizeof(UInt32));
				out.insert(out.end(), value.begin(), value.end());
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				return Type(iter,end);
			}		
		};
		
		
		//	VT_INTEGER,
		//  Conversion type	rules	
		//  boolean	0 => false, all other values => true	
		//  integer	unity	
		//  real	closest representable number	
		//  uuid	n/a	
		//  string	human readable string	
		//  binary	8 byte network byte order representation	
		//  date	seconds since epoch	
		//  uri	n/a
		template<>
		struct LLSDTraits<LLSDValue::VT_INTEGER>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_INTEGER);
			typedef LLSDValue::Integer Type;

			static inline void convert(LLSDValue::Boolean & to, Type const & from)
			{
				to = from != 0;
			}
			static inline void convert(LLSDValue::Integer & to, Type const & from)
			{
				to = from;
			}
			static inline void convert(LLSDValue::Real & to, Type const & from)	
			{
				to = LLSDValue::Real(from);
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to = boost::lexical_cast<LLSDValue::String>(from);
			}
			static inline void convert(LLSDValue::Binary & to, Type const & from)
			{
				Int32 tmp = to_network(from);
				Byte * p = reinterpret_cast<Byte*>(&tmp);
				to.assign(p,p+sizeof(Int32));
			}
			static inline void convert(LLSDValue::Date & to, Type const & from)
			{
				LLSDValue::Date fromDate(from);
				to.swap(fromDate);
			}
			static inline void convert(LLSDValue::URI &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Integer to URI");
			}
			static inline void convert(LLSDValue::UUID &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Integer to UUID");
			}

			static inline String xml_encode(Type const & value)
			{
				return "<integer>" + boost::lexical_cast<String>(value) + "</integer>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				return boost::lexical_cast<Type>(String(iter, end));
			}

			static inline String notation_encode(Type const & value)
			{
				return "i" + boost::lexical_cast<String>(value);
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				return boost::lexical_cast<Type>(String(iter,end));
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				LLSDValue::Binary bin;
				convert(bin, value);
				out.push_back(Byte('i'));
				out.insert(out.end(), bin.begin(), bin.end());
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				LLSDValue::Binary bin(iter,end);
				Type tmp = 0;
				LLSDTraits<LLSDValue::VT_BINARY>::convert(tmp,bin);
				return tmp;
			}
		};




		//	VT_REAL,
		//	Conversion type	rules	
		//	boolean	exactly 0 => false, all other values => true	
		//	integer	rounded to closest representable number	
		//	real	unity	
		//	uuid	n/a	
		//	string	human readable string	
		//	binary	8 byte network byte order representation	
		//	date	seconds since epoch	
		//	uri	n/a
		template<>
		struct LLSDTraits<LLSDValue::VT_REAL>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_REAL);
			typedef LLSDValue::Real Type;

			static inline void convert(LLSDValue::Boolean & to, Type const & from)
			{
				to = (from == Type(0));
			}
			static inline void convert(LLSDValue::Integer & to, Type const & from)
			{
				to = LLSDValue::Integer(from);
			}
			static inline void convert(LLSDValue::Real & to, Type const & from)	
			{
				to = from;
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to = "nan";
				if(!boost::math::isnan(from))
				{
					std::ostringstream tmp;
					tmp.precision(10);
					tmp << from;
					to = tmp.str();
				}
			}
			static inline void convert(LLSDValue::Binary & to, Type const & from)
			{
				Type tmp = to_network(from);
				Byte * p = reinterpret_cast<Byte*>(&tmp);
				to.assign(p,p+sizeof(Type));
			}
			static inline void convert(LLSDValue::Date & to, Type const & from)
			{
				LLSDValue::Date fromDate(from);
				to.swap(fromDate);
			}
			static inline void convert(LLSDValue::URI &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Rela64 to URI");
			}
			static inline void convert(LLSDValue::UUID &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Real64 to UUID");
			}

			static inline String xml_encode(Type const & value)
			{
				String result;
				convert(result,value);
				return "<real>" + result + "</real>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				Type t = 0.0;
				LLSDTraits<LLSDValue::VT_STRING>::convert(t,String(iter,end));
				return t;
			}

			static inline String notation_encode(Type const & value)
			{
				String result;
				convert(result,value);
				return "r" + result;
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				Type t = 0.0;
				LLSDTraits<LLSDValue::VT_STRING>::convert(t,String(iter,end));
				return t;
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				LLSDValue::Binary bin;
				convert(bin, value);
				out.push_back(Byte('r'));
				out.insert(out.end(), bin.begin(), bin.end());
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				LLSDValue::Binary bin(iter,end);
				Type tmp = 0.0;
				LLSDTraits<LLSDValue::VT_BINARY>::convert(tmp,bin);
				return tmp;
			}
		};


		//	VT_UUID,
		//	Conversion type	rules	
		//	boolean	null uuid => false, all other values => true	
		//	integer	n/a	
		//	real	n/a	
		//	uuid	unity	
		//	string	standard 8-4-4-4-12 serialization format	
		//	binary	16 byte raw representation	
		//	date	n/a	
		//	uri	n/a
		template<>
		struct LLSDTraits<LLSDValue::VT_UUID>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_UUID);
			typedef LLSDValue::UUID Type;

			static inline void convert(LLSDValue::Boolean & to, Type const & from)
			{
				to = from.is_zero();
			}
			static inline void convert(LLSDValue::Integer &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from UUID to Integer");
			}
			static inline void convert(LLSDValue::Real &, Type const &)	
			{
				throw BadCastException("Illegal LLSD conversion from UUID to Real64");
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to = from.to_string();
			}
			static inline void convert(LLSDValue::Binary & to, Type const & from)
			{
				from.to_binary().swap(to);
			}
			static inline void convert(LLSDValue::Date &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from UUID to Date");
			}
			static inline void convert(LLSDValue::URI &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from UUID to URI");
			}
			static inline void convert(LLSDValue::UUID & to, Type const & from)
			{
				to = from;
			}

			static inline String xml_encode(Type const & value)
			{
				return "<uuid>" + value.to_string() + "</uuid>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				return Type(String(iter, end));
			}

			static inline String notation_encode(Type const & value)
			{
				return "u" + value.to_string();
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				return Type(String(iter, end));
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				LLSDValue::Binary tmp = value.to_binary();
				out.push_back(Byte('u'));
				out.insert(out.end(), tmp.begin(), tmp.end());
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				byte_sub_range sr(iter, end);
				return Type(sr);
			}
		};

		//	VT_URI,
		//	Conversion type	rules	
		//	boolean	n/a	
		//	integer	n/a	
		//	real	n/a	
		//	uuid	n/a	
		//	string	standard serialization format	
		//	binary	n/a	
		//	date	n/a	
		//	uri	unity
		template<>
		struct LLSDTraits<LLSDValue::VT_URI>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_URI);
			typedef LLSDValue::URI Type;

			static inline void convert(LLSDValue::Boolean &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from URI to Boolean");
			}
			static inline void convert(LLSDValue::Integer &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from URI to Integer");
			}
			static inline void convert(LLSDValue::Real &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from URI to Real64");
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to = from.to_string();
			}
			static inline void convert(LLSDValue::Binary &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from URI to Binary");
			}
			static inline void convert(LLSDValue::Date &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from URI to Date");
			}
			static inline void convert(LLSDValue::URI & to, Type const & from)
			{
				to = from;
			}
			static inline void convert(LLSDValue::UUID &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from URI to UUID");
			}

			static inline String xml_encode(Type const & value)
			{
				return "<url>" + escape_string(value.to_string()) + "</url>";
			}			

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				return Type(String(iter, end));
			}

			static inline String notation_encode(Type const & value)
			{
				return "l\"" + escape_string(value.to_string()) +"\"";
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				return Type(byte_sub_range(iter,end));
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				String uriString = value.to_string();
				UInt32 tmp = to_network(UInt32(uriString.size()));
				Byte const * p  = reinterpret_cast<Byte const*>(&tmp);
				out.push_back('l');
				out.insert(out.end(), p, p + sizeof(UInt32));
				out.insert(out.end(), uriString.begin(), uriString.end());
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				byte_sub_range sr(iter, end);
				return Type(sr);
			}
		};

		//	VT_DATE,
		//	Conversion type	rules	
		//	boolean	n/a	
		//	integer	seconds since epoch	
		//	real	seconds since epoch	
		//	uuid	n/a	
		//	string	standard serialization format	
		//	binary	n/a	
		//	date	unity	
		//	uri	n/a
		template<>
		struct LLSDTraits<LLSDValue::VT_DATE>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_DATE);
			typedef LLSDValue::Date Type;

			static inline void convert(LLSDValue::Boolean &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Date to Boolean");
			}
			static inline void convert(LLSDValue::Integer & to, Type const & from)
			{
				to = from.to_integer();
			}
			static inline void convert(LLSDValue::Real & to, Type const & from)	
			{
				to = from.to_real();
			}
			static inline void convert(LLSDValue::String & to, Type const & from)
			{
				to = from.to_string();
			}
			static inline void convert(LLSDValue::Binary &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Date to Binary");
			}
			static inline void convert(LLSDValue::Date & to, Type const & from)
			{
				to = from;
			}
			static inline void convert(LLSDValue::URI &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Date to URI");
			}
			static inline void convert(LLSDValue::UUID &, Type const &)
			{
				throw BadCastException("Illegal LLSD conversion from Date to UUID");
			}

			static inline String xml_encode(Type const & value)
			{
				return "<date>" + value.to_string() + "</date>";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator iter, Iterator end)
			{
				return Type(String(iter,end));
			}

			static inline String notation_encode(Type const & value)
			{
				return "d\"" + value.to_string() + "\"";
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				return Type(String(iter,end));
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				LLSDValue::Binary bin;
				LLSDTraits<LLSDValue::VT_REAL>::convert(bin, value.to_real());
				out.push_back(Byte('d'));
				out.insert(out.end(), bin.begin(), bin.end());				
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				byte_sub_range sr(iter, end);
				return Type(sr);
			}
		};


		//	VT_ARRAY,
		template<>
		struct LLSDTraits<LLSDValue::VT_ARRAY>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_ARRAY);
			typedef LLSDValue::Array Type;

			static inline String xml_encode(Type const & value)
			{
				String out = "<array>";
				BOOST_FOREACH(Type::value_type const & item, value)
				{
					out += item.xml_encode();
				}
				return out + "</array>";
			}

			// For compatibility it has the signature but actually it does not
			// convert anything
			template<typename Iterator>
			static inline Type xml_decode(Iterator,Iterator)
			{
				return Type();
			}

			static inline String notation_encode(Type const & value)
			{
				String out = "[";
				bool first = true;
				BOOST_FOREACH(Type::value_type const & item, value)
				{
					if(!first)
					{
						out += ',';
					}
					out += item.notation_encode();
					first = false;
				}
				return out + "]";
			}

			// For compatibility it has the signature but actually it does not
			// convert anything
			template<typename Iterator>
			static inline Type notation_decode(Iterator,Iterator)
			{
				return Type();
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				out.push_back(Byte('['));
				UInt32 size = to_network(UInt32(value.size()));
				Byte * p = reinterpret_cast<Byte*>(&size);
				out.insert(out.end(), p, p+sizeof(UInt32));
				BOOST_FOREACH(Type::value_type const & item, value)
				{
					item.binary_encode(out);
				}
				out.push_back(Byte(']'));
			}

			// For compatibility it has the signature but actually it does not
			// convert anything
			template<typename Iterator>
			static inline Type binary_decode(Iterator,Iterator)
			{
				return Type();
			}
		};

		//	VT_MAP
		template<>
		struct LLSDTraits<LLSDValue::VT_MAP>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_MAP);
			typedef LLSDValue::Map Type;

			static inline String xml_encode(Type const & value)
			{
				String out = "<map>";
				BOOST_FOREACH(Type::value_type const & item, value)
				{
					String tmp;
					TiXmlBase::EncodeString(item.first, &tmp);
					out += "<key>" + tmp + "</key>";
					out += item.second.xml_encode();
				}
				return out + "</map>";
			}

			// For compatibility it has the signature but actually it does not
			// convert anything
			template<typename Iterator>
			static inline Type xml_decode(Iterator,Iterator)
			{
				return Type();
			}

			static inline String notation_encode(Type const & value)
			{
				String out = "{";
				bool first = true;
				BOOST_FOREACH(Type::value_type const & item, value)
				{
					if(!first)
					{
						out += ",";
					}
					first = false;
					out += "'" + escape_string(item.first) + "':";
					out += item.second.notation_encode();
				}
				return out + "}";
			}

			// For compatibility it has the signature but actually it does not
			// convert anything
			template<typename Iterator>
			static inline Type notation_decode(Iterator , Iterator)
			{
				return Type();
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const & value)
			{
				out.push_back(Byte('{'));
				UInt32 size = to_network(UInt32(value.size()));
				Byte const * p = reinterpret_cast<Byte const *>(&size);
				out.insert(out.end(), p, p+sizeof(UInt32));
				BOOST_FOREACH(Type::value_type const & item, value)
				{
					LLSDTraits<LLSDValue::VT_STRING>::binary_encode(out, item.first);
					item.second.binary_encode(out);
				}
				out.push_back(Byte('}'));
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator, Iterator)
			{
				return Type();
			}
		};

		template<>
		struct LLSDTraits<LLSDValue::VT_UNDEF>
		{
			static LLSDValue::Types const type_id = LLSDValue::Types(LLSDValue::VT_UNDEF);
			typedef LLSDValue::Undef Type;

			static inline String xml_encode(Type const &)
			{
				return "<undef />";
			}

			template<typename Iterator>
			static inline Type xml_decode(Iterator it, Iterator end)
			{				
				libomvtk_ensure(it == end);
				return Type();
			}

			static inline String notation_encode(Type const &)
			{
				return "!";
			}

			template<typename Iterator>
			static inline Type notation_decode(Iterator iter, Iterator end)
			{
				byte_sub_range sr(iter, end);
				libomvtk_ensure(sr.size() == 1 && char(*iter) == '!');
				return Type();
			}

			static inline void binary_encode(LLSDValue::Binary & out, Type const &)
			{
				out.push_back(omvtk::Byte('!'));
			}

			template<typename Iterator>
			static inline Type binary_decode(Iterator iter, Iterator end)
			{
				byte_sub_range sr(iter, end);
				libomvtk_ensure(sr.size() == 1 && char(*iter) == '!');
				return Type();
			}

		};

		struct LLSDTraitsWrapBase
		{
			typedef boost::function<String(boost::any const &)> EncoderT;
			typedef boost::function<boost::any(byte_sub_range const &)> DecoderT;
			typedef boost::function<void(LLSDValue::Binary & ,boost::any const & value)> BinEncoderT;

			EncoderT xml_encode;
			DecoderT xml_decode;
			EncoderT notation_encode;
			DecoderT notation_decode;
			BinEncoderT binary_encode;
			DecoderT binary_decode;

			LLSDTraitsWrapBase(EncoderT xmlE, EncoderT notationE, BinEncoderT binaryE,
							   DecoderT xmlD, DecoderT notationD, DecoderT binaryD)
							   : xml_encode(xmlE)
							   , xml_decode(xmlD)
							   , notation_encode(notationE)
							   , notation_decode(notationD)
							   , binary_encode(binaryE)
							   , binary_decode(binaryD)
			{}
		};

		template<typename Traits>
		struct LLSDTraitsWrap : LLSDTraitsWrapBase
		{
			LLSDTraitsWrap()
				: LLSDTraitsWrapBase
				(
					&LLSDTraitsWrap::xml_encode_, 
					&LLSDTraitsWrap::notation_encode_,
					&LLSDTraitsWrap::binary_encode_,
					&LLSDTraitsWrap::xml_decode_,
					&LLSDTraitsWrap::notation_decode_,
					&LLSDTraitsWrap::binary_decode_
				)
			{
			}
	
			static LLSDTraitsWrapBase & get_instance()
			{ 
				static LLSDTraitsWrap instance; 
				return instance; 
			}

			static inline String xml_encode_(boost::any const & value)
			{
				return Traits::xml_encode(boost::any_cast<typename Traits::Type>(value));
			}
			
			static inline boost::any xml_decode_(byte_sub_range const & sr)
			{
				return Traits::xml_decode(sr.begin(),sr.end());
			}

			static inline String notation_encode_(boost::any const & value)
			{
				return Traits::notation_encode(boost::any_cast<typename Traits::Type>(value));
			}

			static inline boost::any notation_decode_(byte_sub_range const & sr)
			{
				return Traits::notation_decode(sr.begin(),sr.end());
			}

			static inline void binary_encode_(LLSDValue::Binary & out, boost::any const & value)
			{
				Traits::binary_encode(out, boost::any_cast<typename Traits::Type>(value));
			}

			static inline boost::any binary_decode_(byte_sub_range const & sr)
			{
				return Traits::binary_decode(sr.begin(), sr.end());
			}

		};

		template<typename TargetType>
		struct LLSDConverter
		{
			template<LLSDValue::Types TypeID>
			static void do_convert(TargetType & target, boost::any const & a)
			{
				typedef typename LLSDTraits<TypeID>::Type SourceT;
				LLSDTraits<TypeID>::convert(target, boost::any_cast<SourceT>(a));
			}

			template<LLSDValue::Types TypeID>
			static LLSDTraitsWrapBase & get_wrap_helper()
			{
				return LLSDTraitsWrap< LLSDTraits<TypeID> >::get_instance();
			}

			static LLSDTraitsWrapBase & get_wrap(LLSDValue::Types type_id)
			{
				switch(type_id)
				{
				case LLSDValue::VT_BOOLEAN:
					return get_wrap_helper<LLSDValue::VT_BOOLEAN>();
				case LLSDValue::VT_INTEGER:
					return get_wrap_helper<LLSDValue::VT_INTEGER>();
				case LLSDValue::VT_REAL:
					return get_wrap_helper<LLSDValue::VT_REAL>();
				case LLSDValue::VT_STRING:
					return get_wrap_helper<LLSDValue::VT_STRING>();
				case LLSDValue::VT_UUID:
					return get_wrap_helper<LLSDValue::VT_UUID>();
				case LLSDValue::VT_URI:
					return get_wrap_helper<LLSDValue::VT_URI>();
				case LLSDValue::VT_DATE:
					return get_wrap_helper<LLSDValue::VT_DATE>();
				case LLSDValue::VT_BINARY:
					return get_wrap_helper<LLSDValue::VT_BINARY>();
				case LLSDValue::VT_ARRAY:
					return get_wrap_helper<LLSDValue::VT_ARRAY>();
				case LLSDValue::VT_MAP:
					return get_wrap_helper<LLSDValue::VT_MAP>();
				default: break;
				};
				return get_wrap_helper<LLSDValue::VT_UNDEF>();
			}

			static TargetType convert(boost::any const & a, LLSDValue::Types type_id)
			{
				TargetType target = TargetType();
				switch(type_id)
				{
				case LLSDValue::VT_BOOLEAN:
					do_convert<LLSDValue::VT_BOOLEAN>(target, a); 
					break;
				case LLSDValue::VT_INTEGER:
					do_convert<LLSDValue::VT_INTEGER>(target, a);
					break;
				case LLSDValue::VT_REAL:
					do_convert<LLSDValue::VT_INTEGER>(target, a);
					break;
				case LLSDValue::VT_STRING:
					do_convert<LLSDValue::VT_STRING>(target, a);
					break;
				case LLSDValue::VT_UUID:
					do_convert<LLSDValue::VT_UUID>(target, a);
					break;
				case LLSDValue::VT_URI:
					do_convert<LLSDValue::VT_URI>(target, a);
					break;
				case LLSDValue::VT_DATE:
					do_convert<LLSDValue::VT_DATE>(target, a);
					break;
				case LLSDValue::VT_BINARY:
					do_convert<LLSDValue::VT_BINARY>(target, a);
					break;
				default: break;
				};
				return target;
			}
		};
	}
}
#endif //DOXYGEN_SHOULD_SKIP_THIS
#endif //GUARD_LIBOMVTK_LLSD_LLSD_TRAITS_H_INCLUDED
