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
#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_REQUEST_HEADER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTP_REQUEST_HEADER_H_INCLUDED

#include "http_header.h"

namespace omvtk
{
	struct HTTPRequestHeader
		: HTTPHeader
	{		
		HTTPRequestHeader(LLURI  const & uri, 
						  String const & method = HTTP::METHOD::GET,
						  String const & http_version = HTTP::VERSION11);

		HTTPRequestHeader(String const & host, 
						  String const & request_uri,
						  String const & method,
						  String const & http_version = HTTP::VERSION11);

		HTTPRequestHeader(String const & host, 
						  String const & port, 
						  String const & request_uri,
						  String const & method,
						  String const & http_version);

		HTTPRequestHeader(HTTPRequestHeader const &);
		~HTTPRequestHeader();

		HTTPRequestHeader & operator=(HTTPRequestHeader);
		void swap(HTTPRequestHeader&);

		String const & version() const;
		String & version();

		String const & method() const;
		String & method();

		String const & uri() const;
		String & uri();

		String const & accept() const;
		String & accept();				
		
		String const & accept_charset() const;
		String & accept_charset();

		String const & accept_encoding() const;
		String & accept_encoding();
		
		String const & accept_language() const;
		String & accept_language();
		
		String const & authorization() const;
		String & authorization();

		String const & expect() const;
		String & expect();
		
		String const & from() const;
		String & from();
		
		String const & host() const;
		String & host();
		
		String const & proxy_authorization() const;
		String & proxy_authorization();		

		String const & user_agent() const;
		String & user_agent();

		String const & referer() const;
		String & referer();

		String request_line() const;
		String request() const;
	protected:
		String m_method;
		String m_uri;
		String m_http_version;
	};
}

#endif // GUARD_LIBOMVTK_NETWORK_HTTP_REQUEST_HEADER_H_INCLUDED

