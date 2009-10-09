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
#include "http_response_header.h"
#include <algorithm>

namespace omvtk
{
	HTTPResponseHeader::HTTPResponseHeader()
	: HTTPHeader()
	, m_status_code(200)
	, m_status_message("OK")
	{
		transfer_encoding() = HTTP::TRANSFER_ENCODING_IDENTITY; 
	}
	
	HTTPResponseHeader::HTTPResponseHeader(HTTPResponseHeader const & hrh)
	: HTTPHeader(hrh)
	, m_status_code(hrh.m_status_code)
	, m_status_message(hrh.m_status_message)
	{}
	
	HTTPResponseHeader::~HTTPResponseHeader()
	{}

	HTTPResponseHeader & HTTPResponseHeader::operator=(HTTPResponseHeader hrh)
	{
		swap(hrh);
		return *this;
	}

	void HTTPResponseHeader::swap(HTTPResponseHeader & hrh)
	{
		HTTPHeader::swap(hrh);
		m_status_message.swap(hrh.m_status_message);
		std::swap(hrh.m_status_code, m_status_code);
	}
	
	String const &  HTTPResponseHeader::accept_ranges() const
	{
		return field(HTTP::RESPONSE::FIELD::ACCEPT_RANGES);
	}

	String &  HTTPResponseHeader::accept_ranges()
	{
		return field(HTTP::RESPONSE::FIELD::ACCEPT_RANGES);
	}

	String const &  HTTPResponseHeader::age() const
	{
		return field(HTTP::RESPONSE::FIELD::AGE);
	}
	String &  HTTPResponseHeader::age()
	{
		return field(HTTP::RESPONSE::FIELD::AGE);
	}
		
	String const &  HTTPResponseHeader::etag() const
	{
		return field(HTTP::RESPONSE::FIELD::ETAG);
	}

	String &  HTTPResponseHeader::etag()
	{
		return field(HTTP::RESPONSE::FIELD::ETAG);
	}
		
	String const &  HTTPResponseHeader::location() const
	{
		return field(HTTP::RESPONSE::FIELD::LOCATION);
	}

	String &  HTTPResponseHeader::location()
	{
		return field(HTTP::RESPONSE::FIELD::LOCATION);
	}

	String const &  HTTPResponseHeader::proxy_authenticate() const
	{
		return field(HTTP::RESPONSE::FIELD::PROXY_AUTHENTICATE);
	}

	String &  HTTPResponseHeader::proxy_authenticate()
	{
		return field(HTTP::RESPONSE::FIELD::PROXY_AUTHENTICATE);
	}

	String const &  HTTPResponseHeader::retry_after() const
	{
		return field(HTTP::RESPONSE::FIELD::RETRY_AFTER);
	}

	String &  HTTPResponseHeader::retry_after()
	{
		return field(HTTP::RESPONSE::FIELD::RETRY_AFTER);
	}

	String const &  HTTPResponseHeader::server() const
	{
		return field(HTTP::RESPONSE::FIELD::SERVER);
	}

	String &  HTTPResponseHeader::server()
	{
		return field(HTTP::RESPONSE::FIELD::SERVER);
	}

	String const &  HTTPResponseHeader::vary() const
	{
		return field(HTTP::RESPONSE::FIELD::VARY);
	}

	String &  HTTPResponseHeader::vary()
	{
		return field(HTTP::RESPONSE::FIELD::VARY);
	}

	String const &  HTTPResponseHeader::www_authenticate() const
	{
		return field(HTTP::RESPONSE::FIELD::WWW_AUTHENTICATE);
	}

	String &  HTTPResponseHeader::www_authenticate()
	{
		return field(HTTP::RESPONSE::FIELD::WWW_AUTHENTICATE);
	}
	
	UInt16 HTTPResponseHeader::status_code() const
	{
		return m_status_code;
	}

	UInt16 &  HTTPResponseHeader::status_code()
	{
		return m_status_code;
	}

	String const & HTTPResponseHeader::status_message() const
	{
		return m_status_message;
	}

	String & HTTPResponseHeader::status_message()	
	{
		return m_status_message;
	}
}

