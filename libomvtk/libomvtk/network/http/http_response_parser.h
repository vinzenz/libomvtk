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
#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_PARSER_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_PARSER_H_INCLUDED

#include "http_response.h"
#include "byte_buffer_stream_source.h"

namespace omvtk
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

#endif // GUARD_LIBOMVTK_NETWORK_HTTP_RESPONSE_PARSER_H_INCLUDED

