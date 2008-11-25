#ifndef GUARD_LIBVW_NETWORK_HTTP_HEADER_H_INCLUDED
#define GUARD_LIBVW_NETWORK_HTTP_HEADER_H_INCLUDED

#include "../../types/lluri.h"
#include "../../types/base_types.h"
#include "http_constants.h"
#include <map>
#include <sstream>
#include <boost/algorithm/string/compare.hpp>

namespace vw
{
	struct str_iless
	{
		bool operator()(String const & rhs, String const & lhs) const;
	};
	
	struct HTTPHeader
	{
		HTTPHeader();
		HTTPHeader(HTTPHeader const &);
		~HTTPHeader();
		HTTPHeader & operator=(HTTPHeader hdr);

		String const & field(String const & name) const;
		String & field(String const & name);
		bool has_field(String const & name) const;	
		
		// Entity header fields
		String const & allow() const;
		String & allow();

		String const & content_encoding() const;
		String & content_encoding();

		String const & content_language() const;
		String & content_language();

		String const & content_length() const;
		String & content_length();

		String const & content_location() const;
		String & content_location();

		String const & content_md5() const;
		String & content_md5();

		String const & content_range() const;
		String & content_range();

		String const & content_type() const;
		String & content_type();

		String const & expires() const;
		String & expires();

		String const & last_modified() const;
		String & last_modified();

		// General fields
		String const & transfer_encoding() const;
		String & transfer_encoding();

		String const & cache_control() const;
		String & cache_control();
	
		String const & connection() const;
		String & connection();

		String const & date() const;
		String & date();

		String const & pragma() const;
		String & pragma();

		String const & trailer() const;
		String & trailer();

		String const & upgrade() const;
		String & upgrade();

		String const & via() const;
		String & via();

		String const & warning() const;
		String & warning();

		void swap(HTTPHeader & hdr);	

		String dump() const
		{
			std::ostringstream os;
			dump(os);
			return os.str();
		}

		void dump(std::ostream & os) const
		{
			std::map<String, String, str_iless>::const_iterator iter = m_fields.begin();
			for(;iter != m_fields.end(); ++iter)
			{
				os << iter->first << ":\t" << iter->second << "\n";
			}
		}	
	
	protected:
		std::map<String, String, str_iless> m_fields;
	};
}

#endif // GUARD_LIBVW_NETWORK_HTTP_HEADER_H_INCLUDED

