#pragma once 

#include "llsd_value.h"
#include <boost/static_assert.hpp>

namespace LLSD
{
	struct Real : Value
	{
		Real();
		Real(double value);
		Real(Real const &);
		Real(RealPtr const &);
		virtual ~Real();

		Real & operator=(Real other);

		static RealPtr FromString(std::string const & str);

		double GetValue() const;
		void SetValue(double value);

		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual DatePtr ToDate() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
	protected:
		BOOST_STATIC_ASSERT(sizeof(double) == 8);
		double m_value;
	};
}