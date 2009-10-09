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
#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_HEADER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_HEADER_H_INCLUDED

#include "http_header.h"

namespace omvtk
{
	struct HTTPResponseHeader
		: HTTPHeader
	{
		HTTPResponseHeader();
		HTTPResponseHeader(HTTPResponseHeader const &);
		~HTTPResponseHeader();

		HTTPResponseHeader & operator=(HTTPResponseHeader hrh);
		void swap(HTTPResponseHeader &);
	
		String const & accept_ranges() const;
		String & accept_ranges();

		String const & age() const;
		String & age();
		
		String const & etag() const;
		String & etag();
		
		String const & location() const;
		String & location();

		String const & proxy_authenticate() const;
		String & proxy_authenticate();

		String const & retry_after() const;
		String & retry_after();

		String const & server() const;
		String & server();

		String const & vary() const;
		String & vary();

		String const & www_authenticate() const;
		String & www_authenticate();	
	
		UInt16 status_code() const;
		UInt16 & status_code();

		String const & status_message() const;
		String & status_message();

        void dump(std::ostream & os) const
        {
			os << "Status: " << m_status_code << " Message: " << m_status_message << "\n";
			HTTPHeader::dump(os);
        }
	
	protected:
		UInt16 m_status_code;
		String m_status_message;
	};
}

#endif // GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_HEADER_H_INCLUDED

