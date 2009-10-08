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

    struct LLDate_P{
        LLDate_P(boost::posix_time::ptime d = boost::posix_time::ptime() ) :m_data(d){
            input_facet = new  boost::local_time::local_time_input_facet();
            output_facet = new  boost::local_time::local_time_facet();   

            input_facet->format( omvtk::LLDate::DateFormat.c_str());     
            output_facet->format( omvtk::LLDate::DateFormat.c_str());     

            ss.imbue(std::locale(std::locale::classic(), output_facet));
            ss.imbue(std::locale(ss.getloc(), input_facet));
        }
        ~LLDate_P(){
//            delete input_facet;
//            delete output_facet;
        }
        boost::local_time::local_time_input_facet * input_facet;
        boost::local_time::local_time_facet * output_facet;
		boost::posix_time::ptime m_data;
        std::stringstream ss;
    };

	String const & LLDate::DateFormat = "%Y";

	LLDate::LLDate()
		: d(new LLDate_P(boost::posix_time::from_time_t(0)))
	{		
	}

	LLDate::LLDate(byte_sub_range const & sr)
		: d(new LLDate_P(FromByteSubRange(sr)))
	{		
	}

	LLDate::LLDate(Int32 secondsSinceEpoch)
		: d(new LLDate_P(boost::posix_time::from_time_t(secondsSinceEpoch)))
	{	
	}

	LLDate::LLDate(double secondsSinceEpoch)
		: d(new LLDate_P(boost::posix_time::from_time_t(secondsSinceEpoch)))
	{	
	}

	LLDate::LLDate(String const & fromString)
		: d(new LLDate_P())
	{
        std::stringstream ss(fromString);
        ss>>(*this);
	}

	LLDate::LLDate(LLDate const & o)
        : d(new LLDate_P(o.d->m_data))
	{
        d=new LLDate_P();
	}

    LLDate::~LLDate()
    {
        delete d;
    }


	LLDate & LLDate::operator=(const LLDate & o)
	{
        d->m_data=o.d->m_data;
		return *this;
	}


	bool LLDate::operator == (LLDate const & o) const
	{
		return d->m_data == o.d->m_data;
	}
	
	bool LLDate::operator != (LLDate const & o) const
	{
		return d->m_data != o.d->m_data;
	}
	
	bool LLDate::operator <  (LLDate const & o) const
	{
		return d->m_data < o.d->m_data;
	}
	
	bool LLDate::operator <= (LLDate const & o) const
	{
		return d->m_data <= o.d->m_data;
	}
	
	bool LLDate::operator >  (LLDate const & o) const
	{
		return d->m_data > o.d->m_data;
	}
	
	bool LLDate::operator >= (LLDate const & o) const
	{
		return d->m_data >= o.d->m_data;
	}
	
	void LLDate::swap(LLDate & other)
	{
        std::swap(other.d->m_data,this->d->m_data);
	}
	
	String LLDate::to_string() const
	{
        d->ss<<d->m_data;
        return d->ss.str();
	}

	Int32 LLDate::to_integer() const {
        return static_cast<Int32>(to_real()); 
	}

	Real64 LLDate::to_real() const{
        //if ptime is not_a_date_time or an infinity there's no conversion 
        if (d->m_data.is_special()) { 
            throw new std::runtime_error("conversion undefined"); 
        }

        boost::posix_time::ptime time_t_epoch(boost::gregorian::date(1970,1,1)); 
        //if ptime is less than 1970-1-1 conversion will fail 
        if (d->m_data < time_t_epoch) { 
            throw new std::runtime_error("conversion undefined"); 
        } 
        boost::posix_time::time_duration td = d->m_data - time_t_epoch; 
        return static_cast<std::time_t>(td.total_seconds()); 
	}

	LLDate::value_type const & LLDate::get() const
	{
		return d->m_data;
	}

	LLDate::value_type & LLDate::get()
	{
		return d->m_data;
	}
}

namespace std{

    istream & operator>>(istream & is, omvtk::LLDate & d){
        std::locale oldloc=is.imbue(std::locale(is.getloc(), d.d->input_facet));
        is>>d.get();
        is.imbue(oldloc);
        return is;
	}
    ostream & operator<<(ostream & os, omvtk::LLDate const & d){
        std::locale oldloc=os.imbue(std::locale(std::locale::classic(), d.d->output_facet));
        os<<d.get();
        os.imbue(oldloc);
        return os;
    }
}

