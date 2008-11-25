#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_H_INCLUDED

#include "http_response_header.h"

namespace omvtk
{
	struct HTTPResponse
	{
		typedef HTTPResponseHeader Header;

		HTTPResponse();
		HTTPResponse(HTTPResponse const &);
		~HTTPResponse();

		HTTPResponse & operator=(HTTPResponse hr);

		Header const & header() const;
		Header & header();

		ByteBuffer const & content() const;
		ByteBuffer & content();

		void swap(HTTPResponse & hr);		
	protected:
		Header m_header;
		ByteBuffer m_content;		
	};
}

#endif // GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_H_INCLUDED

