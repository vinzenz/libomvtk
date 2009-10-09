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
#include "http_constants.h"


namespace omvtk
{
	namespace HTTP
	{
		String const VERSION10 = "HTTP/1.0";
		String const VERSION11 = "HTTP/1.1";

		namespace METHOD
		{
			String const GET = "GET";
			String const POST = "POST";
			String const OPTIONS = "OPTIONS";
			String const HEAD = "HEAD";
			String const PUT = "PUT";
			String const DELETE = "DELETE";
			String const TRACE = "TRACE";
			String const CONNECT = "CONNECT";
		}

		String const TRANSFER_ENCODING_CHUNKED = "Chunked";
		String const TRANSFER_ENCODING_IDENTITY = "Identity";

		namespace FIELD
		{
			//general header
			String const CACHE_CONTROL = "Cache-Control";
			String const CONNECTION = "Connection";
			String const DATE = "Date";
			String const PRAGMA = "Pragma";
			String const TRAILER = "Trailer";
			String const TRANSFER_ENCODING = "Transfer-Encoding";
			String const UPGRADE = "Upgrade";
			String const VIA = "Via";
			String const WARNING = "Warning";

			//entity header
			String const ALLOW = "Allow";
			String const CONTENT_ENCODING = "Content-Encoding";
			String const CONTENT_LANGUAGE = "Content-Language";
			String const CONTENT_LENGTH = "Content-Length";
			String const CONTENT_LOCATION = "Content-Location";
			String const CONTENT_MD5 = "Content-MD5";
			String const CONTENT_RANGE = "Content-Range";
			String const CONTENT_TYPE = "Content-Type";
			String const EXPIRES = "Expires";
			String const LAST_MODIFIED = "Last-Modified";
		}

		namespace REQUEST
		{
			namespace FIELD
			{
				String const ACCEPT = "Accept";
				String const ACCEPT_CHARSET = "Accept-Charset";
				String const ACCEPT_ENCODING = "Accept-Encoding";
				String const ACCEPT_LANGUAGE = "Accept-Language";
				String const AUTHORIZATION = "Authorization";
				String const EXPECT = "Expect";
				String const FROM = "From";
				String const HOST = "Host";
				String const IF_MATCH = "If-Match";
				String const IF_MODIFIED_SINCE = "If-Modified-Since";
				String const IF_NONE_MATCH = "If-None-Match";
				String const IF_RANGE = "If-Range";
				String const IF_UNMODIFIED_SINCE = "If-Unmodified-Since";
				String const MAX_FORWARDS = "Max-Forwards";	
				String const PROXY_AUTHORIZATION = "Proxy-Authorization";
				String const RANGE = "Range";
				String const REFERER = "Referer";
				String const TE = "TE";
				String const USER_AGENT = "User-Agent";
			}			
		}

		namespace RESPONSE
		{
			namespace FIELD
			{
				String const ACCEPT_RANGES = "Accept-Ranges";
				String const AGE = "Age";
				String const ETAG = "ETag";
				String const LOCATION = "Location";
				String const PROXY_AUTHENTICATE = "Proxy-Authenticate";
				String const RETRY_AFTER = "Retry-After";
				String const SERVER = "Server";
				String const VARY = "Vary";
				String const WWW_AUTHENTICATE = "WWW-Authenticate";
			}
		}
	}
}

