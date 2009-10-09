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
#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_CONSTANTS_H_INCLUDED
#define GUARD_LIBOMVTK_NETWORK_HTTP_CONSTANTS_H_INCLUDED

#include "../../types/base_types.h"

namespace omvtk
{
	namespace HTTP
	{
		extern String const VERSION10;
		extern String const VERSION11;

		namespace METHOD
		{
			extern String const GET;
			extern String const POST;
			extern String const OPTIONS;
			extern String const HEAD;
			extern String const PUT;
			extern String const DELETE;
			extern String const TRACE;
			extern String const CONNECT;
		}

		extern String const TRANSFER_ENCODING_CHUNKED;
		extern String const TRANSFER_ENCODING_IDENTITY;

		namespace FIELD
		{
			//general header
			extern String const CACHE_CONTROL;
			extern String const CONNECTION;
			extern String const DATE;
			extern String const PRAGMA;
			extern String const TRAILER;
			extern String const TRANSFER_ENCODING;
			extern String const UPGRADE;
			extern String const VIA;
			extern String const WARNING;

			//entity header
			extern String const ALLOW;
			extern String const CONTENT_ENCODING;
			extern String const CONTENT_LANGUAGE;
			extern String const CONTENT_LENGTH;
			extern String const CONTENT_LOCATION;
			extern String const CONTENT_MD5;
			extern String const CONTENT_RANGE;
			extern String const CONTENT_TYPE;
			extern String const EXPIRES;
			extern String const LAST_MODIFIED;
		}

		namespace REQUEST
		{
			namespace FIELD
			{
				extern String const ACCEPT;
				extern String const ACCEPT_CHARSET;
				extern String const ACCEPT_ENCODING;
				extern String const ACCEPT_LANGUAGE;
				extern String const AUTHORIZATION;
				extern String const EXPECT;
				extern String const FROM;
				extern String const HOST;
				extern String const IF_MATCH;
				extern String const IF_MODIFIED_SINCE;
				extern String const IF_NONE_MATCH;
				extern String const IF_RANGE;
				extern String const IF_UNMODIFIED_SINCE;
				extern String const MAX_FORWARDS;	
				extern String const PROXY_AUTHORIZATION;
				extern String const RANGE;
				extern String const REFERER;
				extern String const TE;
				extern String const USER_AGENT;
			}			
		}

		namespace RESPONSE
		{
			namespace FIELD
			{
				extern String const ACCEPT_RANGES;
				extern String const AGE;
				extern String const ETAG;
				extern String const LOCATION;
				extern String const PROXY_AUTHENTICATE;
				extern String const RETRY_AFTER;
				extern String const SERVER;
				extern String const VARY;
				extern String const WWW_AUTHENTICATE;
			}
		}
	}
}

#endif //GUARD_LIBOMVTK_NETWORK_HTTP_CONSTANTS_H_INCLUDED

