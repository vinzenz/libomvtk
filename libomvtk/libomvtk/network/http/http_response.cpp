#include "http_response.h"

namespace omvtk
{
	HTTPResponse::HTTPResponse()
	: m_header()
	, m_content()
	{}

	HTTPResponse::HTTPResponse(HTTPResponse const & hr)
	: m_header(hr.m_header)
	, m_content(hr.m_content)
	{}
	
	HTTPResponse::~HTTPResponse()
	{}
	
	HTTPResponse & HTTPResponse::operator=(HTTPResponse hr)
	{
		swap(hr);
		return *this;
	}

	void HTTPResponse::swap(HTTPResponse & hr)
	{
		m_header.swap(hr.m_header);
		m_content.swap(hr.m_content);
	}
	
	HTTPResponse::Header const & HTTPResponse::header() const
	{
		return m_header;
	}
	HTTPResponse::Header & HTTPResponse::header()
	{
		return m_header;
	}
	ByteBuffer const & HTTPResponse::content() const
	{
		return m_content;
	}
	ByteBuffer & HTTPResponse::content()
	{
		return m_content;
	}
}

