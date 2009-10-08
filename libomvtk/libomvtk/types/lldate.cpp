#include "lldate.h"
#include <iostream>
#include <locale>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <ctime>
#include <cassert>


namespace 
{
	omvtk::LLDate::value_type FromByteSubRange(omvtk::byte_sub_range const & sr)
	{
		libomvtk_ensure(sr.size() == sizeof(omvtk::Real64));
		omvtk::Real64 r = *(omvtk::Real64*)&sr[0];
//		r = omvtk::Real64ByteOrder::convert(Poco::ByteOrder::fromNetwork, r);
		return boost::posix_time::from_time_t(r);
	}
}

namespace omvtk
{
	String const & LLDate::DateFormat = "%Y-%m-%dT%H:%M:%S%F%z";

	LLDate::LLDate()
		: m_data(boost::posix_time::from_time_t(0))
	{		
	}

	LLDate::LLDate(byte_sub_range const & sr)
		: m_data(FromByteSubRange(sr))
	{		
	}

	LLDate::LLDate(Int32 secondsSinceEpoch)
		: m_data(boost::posix_time::from_time_t(secondsSinceEpoch))
	{		
	}

	LLDate::LLDate(double secondsSinceEpoch)
		: m_data(boost::posix_time::from_time_t(secondsSinceEpoch))
	{		
	}

	LLDate::LLDate(String const & fromString)
		: m_data(boost::posix_time::from_time_t(0))
	{
        std::stringstream ss(fromString);
        ss>>(*this);
	}

	LLDate::LLDate(LLDate const & o)
		: m_data(o.m_data)
	{
	}


	LLDate & LLDate::operator=(LLDate o)
	{
		swap(o);
		return *this;
	}


	bool LLDate::operator == (LLDate const & o) const
	{
		return m_data == o.m_data;
	}
	
	bool LLDate::operator != (LLDate const & o) const
	{
		return m_data != o.m_data;
	}
	
	bool LLDate::operator <  (LLDate const & o) const
	{
		return m_data < o.m_data;
	}
	
	bool LLDate::operator <= (LLDate const & o) const
	{
		return m_data <= o.m_data;
	}
	
	bool LLDate::operator >  (LLDate const & o) const
	{
		return m_data > o.m_data;
	}
	
	bool LLDate::operator >= (LLDate const & o) const
	{
		return m_data >= o.m_data;
	}
	
	void LLDate::swap(LLDate & other)
	{
        std::swap(other.m_data,this->m_data);
	}
	
	String LLDate::to_string() const
	{
        std::stringstream ss;
        ss<<(*this);
        return ss.str();
	}

	Int32 LLDate::to_integer() const {
        return static_cast<Int32>(to_real()); 
	}

	Real64 LLDate::to_real() const{
        //if ptime is not_a_date_time or an infinity there's no conversion 
        if (m_data.is_special()) { 
            throw new std::runtime_error("conversion undefined"); 
        }

        boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970,1,1)); 
        //if ptime is less than 1970-1-1 conversion will fail 
        if (m_data < time_t_epoch) { 
            throw new std::runtime_error("conversion undefined"); 
        } 
        boost::posix_time::time_duration td = m_data - time_t_epoch; 
        return static_cast<std::time_t>(td.total_seconds()); 
	}

	LLDate::value_type const & LLDate::get() const
	{
		return m_data;
	}

	LLDate::value_type & LLDate::get()
	{
		return m_data;
	}
}

namespace std{

    istream & operator>>(istream & is, omvtk::LLDate & d){
        boost::local_time::local_time_input_facet  * input_facet = new  boost::local_time::local_time_input_facet();
        input_facet->format( omvtk::LLDate::DateFormat.c_str());
        std::locale oldloc=is.imbue(std::locale(is.getloc(), input_facet));
        is>>d;
        is.imbue(oldloc);
	}
    ostream & operator<<(ostream & os, omvtk::LLDate const & d){
        boost::local_time::local_time_facet  * output_facet = new  boost::local_time::local_time_facet();
        output_facet->format( omvtk::LLDate::DateFormat.c_str());
        std::locale oldloc=os.imbue(std::locale(std::locale::classic(), output_facet));
        os<<d;
        os.imbue(oldloc);
    }
}

