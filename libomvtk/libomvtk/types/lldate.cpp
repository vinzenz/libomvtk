#include "lldate.h"
#include "byte_order.h"
#include <iostream>
#include <locale>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/lexical_cast.hpp>
#include <cstring>
#include <ctime>
#include <cassert>


namespace 
{
    using namespace boost::posix_time;

	omvtk::LLDate::value_type FromByteSubRange(omvtk::byte_sub_range const & sr)
	{
		libomvtk_ensure(sr.size() == sizeof(omvtk::Real64));
		omvtk::Real64 r = *(omvtk::Real64*)&sr[0];
		return from_time_t( omvtk::to_host(r) );
	}

	omvtk::LLDate::value_type FromString(omvtk::String const & s)
	{
        std::istringstream istr(s);
        omvtk::LLDate d;
        istr >> d;
		return d.get();
	}

    
}

namespace omvtk
{
	String const LLDate::DateFormat = "%Y-%m-%dT%H:%M:%S";

	LLDate::LLDate()
		: m_data(from_time_t(0))
	{		
	}

	LLDate::LLDate(byte_sub_range const & sr)
		: m_data(FromByteSubRange(sr))
    {	
	}

	LLDate::LLDate(Int32 secondsSinceEpoch)
		: m_data(from_time_t(secondsSinceEpoch))
	{	
	}

	LLDate::LLDate(double secondsSinceEpoch)
		: m_data(from_time_t(secondsSinceEpoch))
	{	
	}

	LLDate::LLDate(String const & fromString)
		: m_data(FromString(fromString))
	{
	}

	LLDate::LLDate(LLDate const & o)
        : m_data(o.m_data)
	{
	}

    LLDate::~LLDate()
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
        std::swap( m_data, other.m_data );
	}
	
	String LLDate::to_string() const
	{
        std::ostringstream ostr;        
        ostr << *this;
        return ostr.str();
	}

	Int32 LLDate::to_integer() const {
        return static_cast<Int32>(to_real()); 
	}

	Real64 LLDate::to_real() const{
        //if ptime is not_a_date_time or an infinity there's no conversion 
        if (m_data.is_special()) { 
            throw std::runtime_error("conversion undefined"); 
        }

        ptime time_t_epoch(boost::gregorian::date(1970,1,1)); 
        //if ptime is less than 1970-1-1 conversion will fail 
        if (m_data < time_t_epoch) { 
            throw std::runtime_error("conversion undefined"); 
        } 
        time_duration td = m_data - time_t_epoch; 
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

    istream & operator>>(istream & is, omvtk::LLDate & d)
    {
        std::locale old = is.imbue(
            std::locale(
                is.getloc(),
                new time_input_facet( (omvtk::LLDate::DateFormat).c_str() )
            )
        );
        is >> d.get();
        is.imbue( old );
        
        if( !d.get().is_special() )
        {
            switch( is.peek() ) {
                
                case 'Z':
                    is.get();
                    break;
                case '.':                
                    is.get();
                    {
                        std::string frac;
                        while( is.peek() != -1 ) {
                            char next = is.peek();
                            if( std::isdigit( next ) ) {
                                frac += is.get();
                                continue;
                            }
                            else if( next == 'Z' ) {
                                is.get();
                                if( !frac.empty() ){
                                    d.get() = d.get() + time_duration(0, 0, 0, boost::lexical_cast<omvtk::UInt64>( frac ) );
                                }
                                break;  
                            }
                            break;
                        }
                    }
                    break;
            }
        }
        return is;        
	}
    
    ostream & operator<<(ostream & os, omvtk::LLDate const & d)
    {
        std::locale old = os.imbue(
            std::locale(
                os.getloc(),
                new time_facet( omvtk::LLDate::DateFormat.c_str() )
            )
        );
        os << d.get();
        os.imbue( old );

        if( !d.get().is_special() ) {
            if( d.get().time_of_day().fractional_seconds() ) {
                os << "." << d.get().time_of_day().fractional_seconds();
            }
            os << "Z";
        }
        return os;        
    }
}

