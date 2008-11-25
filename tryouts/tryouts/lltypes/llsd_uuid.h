#pragma once

#include "llsd_value.h"
#include <vector>
#include <Poco/UUID.h>

namespace LLSD
{
	struct UUID : Value
	{
		typedef Poco::UUID value_type;
		static UUID Zero;

		UUID();
		UUID(std::string const &);
		UUID(value_type const &);
		UUID(std::vector<boost::uint8_t> const &);
		UUID(UUID const &);
		UUID(UUIDPtr const &);
		virtual ~UUID();

		bool IsZero() const;
		static std::string ToString(UUID const &);
		static value_type ToRaw(std::string const &);

		value_type const & GetValue() const;
		void SetValue(value_type const & );
		void SetValue(std::vector<boost::uint8_t> const &);
		void SetValue(std::string const & value);

		virtual StringPtr ToString() const;
		virtual UUIDPtr ToUUID() const;
		virtual BooleanPtr ToBoolean() const;
		virtual BinaryPtr ToBinary() const;
	protected:
		value_type m_value;
	};
}