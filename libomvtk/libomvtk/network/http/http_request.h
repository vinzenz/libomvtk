#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_REQUEST_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTP_REQUEST_H_INCLUDED

#include "http_request_header.h"

namespace omvtk
{
	struct HTTPRequest
	{
		HTTPRequest(LLURI const & uri, 
				    String const & method = HTTP::METHOD::GET,
				    String const & http_version = HTTP::VERSION11);

		HTTPRequest(String const & host, 
				    String const & request_uri,
					String const & method,
					String const & http_version = HTTP::VERSION11);

		HTTPRequest(String const & host, 
				    String const & port, 
				    String const & request_uri,
				    String const & method,
				    String const & http_version = HTTP::VERSION11);
		
		HTTPRequest(HTTPRequest const &);
		~HTTPRequest();
		
		HTTPRequest & operator=(HTTPRequest);
		void swap(HTTPRequest &);

		HTTPRequestHeader & header();	
		HTTPRequestHeader const & header() const;	
		
		ByteBuffer & content();
		ByteBuffer const & content() const;

		void build(ByteBuffer & buf) const;
	protected:
		HTTPRequestHeader m_header;
		ByteBuffer m_content;
	};
}

#endif //GUARD_LIBOMVTK_NETWORK_HTTP_REQUEST_H_INCLUDED

