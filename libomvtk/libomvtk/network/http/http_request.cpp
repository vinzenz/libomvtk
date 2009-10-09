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
#include "http_request.h"
#include <boost/lexical_cast.hpp>

namespace omvtk
{

	HTTPRequest::HTTPRequest(LLURI  const & uri, 
						     String const & method,
				    		 String const & http_version)
	: m_header(uri, method, http_version)
	, m_content()
	{}

	HTTPRequest::HTTPRequest(String const & host, 
				    		 String const & request_uri,
							 String const & method,
							 String const & http_version)
	: m_header(host, request_uri, method, http_version)
	, m_content()
	{}

	HTTPRequest::HTTPRequest(String const & host, 
						     String const & port, 
				    		 String const & request_uri,
				    		 String const & method,
				    		 String const & http_version)
	: m_header(host, port, request_uri, method, http_version)
	, m_content()
	{
	}

	HTTPRequest::HTTPRequest(HTTPRequest const & hr)
	: m_header(hr.m_header)
	, m_content(hr.m_content)
	{
	}

	HTTPRequest::~HTTPRequest()
	{
	}
		
	HTTPRequest & HTTPRequest::operator=(HTTPRequest hr)
	{
		swap(hr);
		return *this;
	}



	void HTTPRequest::swap(HTTPRequest & hr)
	{
		hr.header().swap(m_header);
		hr.content().swap(m_content);
	}

	HTTPRequestHeader & HTTPRequest::header()	
	{
		return m_header;
	}

	HTTPRequestHeader const & HTTPRequest::header() const	
	{
		return m_header;
	}
		
	ByteBuffer & HTTPRequest::content()
	{
		return m_content;
	}

	ByteBuffer const & HTTPRequest::content() const
	{
		return m_content;
	}

	void HTTPRequest::build(ByteBuffer & buf) const
	{
//		const_cast<HTTPRequest*>(this)->m_header.content_length() = boost::lexical_cast<String>(buf.size());
		String req = header().request();
		buf.assign(req.begin(),req.end());
		buf.insert(buf.end(), m_content.begin(),m_content.end());		
	}
}

