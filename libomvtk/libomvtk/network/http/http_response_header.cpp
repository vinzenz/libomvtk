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

