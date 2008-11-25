#pragma once

#include "llsd_value.h"

namespace LLSD
{
	struct Integer : Value
	{
		Integer();
		Integer(boost::int32_t value);
		Integer(IntegerPtr const & p);
		Integer(Integer const & o);
		virtual ~Integer();
		Integer & operator=(Integer o);

		static IntegerPtr FromString(std::string const & str);

		boost::int32_t GetValue() const;
		void SetValue(boost::uint32_t const & v);

		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual DatePtr ToDate() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
	protected:
		boost::int32_t m_value;
	};
}