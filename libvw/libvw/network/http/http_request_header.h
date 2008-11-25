#ifndef GUARD_LIBVW_NETWORK_HTTP_REQUEST_HEADER_H_INCLUDED
#define GUARD_LIBVW_NETWORK_HTTP_REQUEST_HEADER_H_INCLUDED

#include "http_header.h"

namespace vw
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

#endif // GUARD_LIBVW_NETWORK_HTTP_REQUEST_HEADER_H_INCLUDED

