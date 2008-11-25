#ifndef GUARD_LIBVW_NETWORK_HTTP_RESPONSE_HEADER_H_INCLUDED
#define GUARD_LIBVW_NETWORK_HTTP_RESPONSE_HEADER_H_INCLUDED

#include "http_header.h"

namespace vw
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

#endif // GUARD_LIBVW_NETWORK_HTTP_RESPONSE_HEADER_H_INCLUDED

