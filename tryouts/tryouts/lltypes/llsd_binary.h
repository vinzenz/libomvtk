#pragma once

#include "llsd_value.h"
#include <vector>

namespace LLSD
{
	struct Binary : Value
	{
		typedef std::vector<boost::uint8_t> Container;
		Binary();
		Binary(boost::uint8_t const * buffer, size_t buffer_size);
		
		template<typename BinaryIterator>
		Binary(BinaryIterator begin, BinaryIterator end)
			: Value(VTID_BINARY)
			, m_value(begin,end)
		{

		}
		Binary(Container const & buf);
		Binary(Binary const &);
		Binary(BinaryPtr const &);
		virtual ~Binary();

		static BinaryPtr FromBase64(std::string const & str);
		static BinaryPtr FromBase64(std::wstring const & str);
		std::string ToBase64();

		Binary & operator=(Binary);

		Container const & GetValue() const;
		void SetValue(Container const & );
		void SetValue(boost::uint8_t const * buffer, size_t buffer_size);

		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual UUIDPtr ToUUID() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
		virtual UriPtr ToUri() const;
	protected:
		Container m_value;
	};
}