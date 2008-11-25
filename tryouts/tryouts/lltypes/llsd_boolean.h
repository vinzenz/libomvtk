#pragma once

#include "llsd_value.h"

namespace LLSD
{
	struct Boolean :public Value
	{
		Boolean();
		Boolean(bool);
		Boolean(Boolean const &);
		Boolean(BooleanPtr const &);

		virtual ~Boolean();
		Boolean & operator=(Boolean o);

		bool GetValue() const;
		void SetValue(bool);

		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
	protected: 
		bool m_value;
	};
}

