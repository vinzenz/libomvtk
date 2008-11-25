#include "http_request.h"
#include <boost/lexical_cast.hpp>

namespace vw
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

