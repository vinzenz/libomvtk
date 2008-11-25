#pragma once 

#include "llsd_value.h"
#include <boost/date_time/posix_time/ptime.hpp>

namespace LLSD 
{
	struct Date : LLSD::Value
	{
		Date();
		Date(boost::int32_t secsSinceEpoch);
		Date(Date const & );
		Date(DatePtr const & );
		Date(boost::posix_time::ptime const & p);
		virtual ~Date();

		static std::string MakeIso(DatePtr const & ptr);
		static std::string MakeIso(Date const & ptr);
		static DatePtr CreateFromISOString(std::string const & str);

		Date & operator=(Date d);

		boost::posix_time::ptime const & GetValue() const;
		void SetValue(boost::posix_time::ptime const & value);
		boost::uint32_t GetSeconds() const;


		virtual IntegerPtr ToInteger() const;
		virtual RealPtr ToReal() const;
		virtual StringPtr ToString() const;
		virtual DatePtr ToDate() const;

	protected:
		boost::posix_time::ptime m_value;
	};
}
