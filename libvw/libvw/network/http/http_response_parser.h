#ifndef GUARD_LIBVW_NETWORK_HTTP_RESPONSE_PARSER_H_INCLUDED
#define GUARD_LIBVW_NETWORK_HTTP_RESPONSE_PARSER_H_INCLUDED

#include "http_response.h"
#include "byte_buffer_stream_source.h"

namespace vw
{
	struct HTTPResponseParser
	{
		HTTPResponseParser(ByteBuffer const &);
		HTTPResponseParser(HTTPResponseParser const &);
		~HTTPResponseParser();

		HTTPResponseParser & operator=(HTTPResponseParser);

		HTTPResponse const & get() const;
		HTTPResponse & get();
		void swap(HTTPResponseParser&);
	protected:
		void parse();		
		void parse_header(std::istream &);
		void parse_version(std::istream &);
		void parse_chunked(std::istream &);
		void parse_identity(std::istream &);

		CharStreamByteBuffer m_buffer;
		HTTPResponse m_response;
	};
}

#endif // GUARD_LIBVW_NETWORK_HTTP_RESPONSE_PARSER_H_INCLUDED

