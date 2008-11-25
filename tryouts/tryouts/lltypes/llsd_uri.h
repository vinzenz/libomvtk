#pragma once

#include "llsd_value.h"
#include <Poco/URI.h>

namespace LLSD
{
	//FIXME: We don't care valid or invalid URIs
	struct Uri : Value
	{
		Uri();
		Uri(Poco::URI const & uri);
		Uri(std::string const & uri);
		Uri(Uri const &);
		Uri(UriPtr const &);
		virtual ~Uri();

		Uri & operator=(Uri);

		Poco::URI const & GetValue();
		void SetValue(Poco::URI const &);

		virtual StringPtr ToString() const;
		virtual UriPtr ToUri() const;
	protected:
		Poco::URI m_value;
	};
}