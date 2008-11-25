#ifndef GUARD_LIBVW_NETWORK_HTTP_CONSTANTS_H_INCLUDED
#define GUARD_LIBVW_NETWORK_HTTP_CONSTANTS_H_INCLUDED

#include "../../types/base_types.h"

namespace vw
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

#endif //GUARD_LIBVW_NETWORK_HTTP_CONSTANTS_H_INCLUDED

