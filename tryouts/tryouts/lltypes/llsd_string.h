#pragma once

#include "llsd_value.h"

namespace LLSD
{
	struct String : Value
	{
		String();
		String(std::string const &);
		String(String const &);
		String(StringPtr const &);
		virtual ~String();

		String & operator=(String o);

		std::string const & GetValue() const;
		void SetValue(std::string const & );

		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual DatePtr ToDate() const;
		virtual UUIDPtr ToUUID() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
		virtual UriPtr ToUri() const;

	protected:
		std::string m_value;
	};
}