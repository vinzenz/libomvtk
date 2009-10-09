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
#include "http_header.h"
#include <boost/algorithm/string/predicate.hpp>
namespace omvtk
{
	bool str_iless::operator()(String const & rhs, String const & lhs) const
	{
		return boost::algorithm::ilexicographical_compare(rhs,lhs);
	}

	HTTPHeader::HTTPHeader()
	: m_fields()
	{}
	
	HTTPHeader::HTTPHeader(HTTPHeader const & hdr)
	: m_fields(hdr.m_fields)
	{}
	
	HTTPHeader::~HTTPHeader()
	{}

	HTTPHeader & HTTPHeader::operator=(HTTPHeader hdr)
	{
		swap(hdr);
		return *this;
	}

	String const & HTTPHeader::field(String const & name) const
	{
		static String const emptyDef;
		if(!has_field(name))
		{
			return emptyDef;
		}
		return m_fields.find(name)->second;
	}

	String & HTTPHeader::field(String const & name)
	{
		return m_fields[name];
	}
	
	bool HTTPHeader::has_field(String const & name) const
	{
		return m_fields.count(name) != 0;
	}

	String const & HTTPHeader::allow() const	
	{
		return field(HTTP::FIELD::ALLOW);
	}
	
	String & HTTPHeader::allow()
	{
		return field(HTTP::FIELD::ALLOW);
	}

	String const & HTTPHeader::content_encoding() const
	{
		return field(HTTP::FIELD::CONTENT_ENCODING);
	}
	
	String & HTTPHeader::content_encoding()
	{
		return field(HTTP::FIELD::CONTENT_ENCODING);
	}

	String const & HTTPHeader::content_language() const
	{
		return field(HTTP::FIELD::CONTENT_LANGUAGE);
	}
	
	String & HTTPHeader::content_language()
	{
		return field(HTTP::FIELD::CONTENT_LANGUAGE);
	}

	String const & HTTPHeader::content_length() const
	{
		return field(HTTP::FIELD::CONTENT_LENGTH);
	}
	
	String & HTTPHeader::content_length()
	{
		return field(HTTP::FIELD::CONTENT_LENGTH);
	}

	String const & HTTPHeader::content_location() const
	{
		return field(HTTP::FIELD::CONTENT_LOCATION);
	}
	
	String & HTTPHeader::content_location()
	{
		return field(HTTP::FIELD::CONTENT_LOCATION);
	}

	String const & HTTPHeader::content_md5() const
	{
		return field(HTTP::FIELD::CONTENT_MD5);
	}
	
	String & HTTPHeader::content_md5()
	{
		return field(HTTP::FIELD::CONTENT_MD5);
	}

	String const & HTTPHeader::content_range() const
	{
		return field(HTTP::FIELD::CONTENT_RANGE);
	}
	
	String & HTTPHeader::content_range()
	{
		return field(HTTP::FIELD::CONTENT_RANGE);
	}

	String const & HTTPHeader::content_type() const
	{
		return field(HTTP::FIELD::CONTENT_TYPE);
	}

	String & HTTPHeader::content_type()
	{
		return field(HTTP::FIELD::CONTENT_TYPE);
	}

	String const & HTTPHeader::expires() const
	{
		return field(HTTP::FIELD::EXPIRES);
	}

	String & HTTPHeader::expires()
	{
		return field(HTTP::FIELD::EXPIRES);
	}
	
	String const & HTTPHeader::last_modified() const
	{
		return field(HTTP::FIELD::LAST_MODIFIED);
	}
	
	String & HTTPHeader::last_modified()
	{
		return field(HTTP::FIELD::LAST_MODIFIED);
	}
	
	String const & HTTPHeader::transfer_encoding() const
	{
		return field(HTTP::FIELD::TRANSFER_ENCODING);
	}

	String & HTTPHeader::transfer_encoding()
	{
		return field(HTTP::FIELD::TRANSFER_ENCODING);
	}

	String const & HTTPHeader::cache_control() const
	{
		return field(HTTP::FIELD::TRANSFER_ENCODING);
	}
	
	String & HTTPHeader::cache_control()
	{
		return field(HTTP::FIELD::CACHE_CONTROL);
	}
	
	String const & HTTPHeader::connection() const
	{
		return field(HTTP::FIELD::CONNECTION);
	}
	
	String & HTTPHeader::connection()
	{
		return field(HTTP::FIELD::CONNECTION);
	}

	String const & HTTPHeader::date() const
	{
		return field(HTTP::FIELD::DATE);
	}

	String & HTTPHeader::date()
	{
		return field(HTTP::FIELD::DATE);
	}

	String const & HTTPHeader::pragma() const
	{
		return field(HTTP::FIELD::PRAGMA);
	}

	String & HTTPHeader::pragma()
	{
		return field(HTTP::FIELD::PRAGMA);
	}

	String const & HTTPHeader::trailer() const
	{
		return field(HTTP::FIELD::TRAILER);
	}

	String & HTTPHeader::trailer()
	{
		return field(HTTP::FIELD::TRAILER);
	}

	String const & HTTPHeader::upgrade() const
	{
		return field(HTTP::FIELD::UPGRADE);
	}

	String & HTTPHeader::upgrade()
	{
		return field(HTTP::FIELD::UPGRADE);
	}

	String const & HTTPHeader::via() const
	{
		return field(HTTP::FIELD::VIA);
	}

	String & HTTPHeader::via()
	{
		return field(HTTP::FIELD::VIA);
	}

	String const & HTTPHeader::warning() const
	{
		return field(HTTP::FIELD::WARNING);
	}

	String & HTTPHeader::warning()
	{
		return field(HTTP::FIELD::WARNING);
	}

	void HTTPHeader::swap(HTTPHeader & hdr)
	{
		m_fields.swap(hdr.m_fields);
	}
}

