#ifndef GUARD_LIBOMVTK_NETWORK_HTTP_BYTE_BUFFER_STREAM_SOURCE_H
#define GUARD_LIBOMVTK_NETWORK_HTTP_BYTE_BUFFER_STREAM_SOURCE_H

#include "../../types/base_types.h"
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/stream_buffer.hpp>

namespace omvtk
{

	template<typename CharT>
	struct byte_buffer_stream_source 
	{	
    	typedef CharT 						  char_type;
		struct category
			: virtual boost::iostreams::device_tag 
			, virtual boost::iostreams::input
			, virtual boost::iostreams::seekable{};
	
	    byte_buffer_stream_source(ByteBuffer const & buf) 
        : buf_(buf), pos_(0)
        { }

		std::streamsize write(char_type const*,std::streamsize){return-1;}

	    std::streamsize read(char_type* s, std::streamsize n)
    	{
	        using namespace std;
    	    streamsize amt = static_cast<streamsize>(buf_.size() - pos_);
        	streamsize result = (min)(n, amt);
	        if (result > 0)
			{
    	        std::copy( reinterpret_cast<char_type const*>(&buf_[pos_]), 
        	               reinterpret_cast<char_type const*>(&buf_[pos_ + result]), 
            	           s );
	            pos_ += result;
    	        return result;
        	} 
            return -1; // EOF	       
    	}
	    std::streamsize seek(std::streamsize off, std::ios::seekdir way)
    	{
        	using namespace std;

	        // Determine new value of pos_
    	    int next;
        	if (way == std::ios::beg) 
			{
	            next = off;
    	    } 
			else if (way == std::ios::cur) 
			{
        	    next = pos_ + off;
	        } 
			else if (way == std::ios::end) 
			{
    	        next = buf_.size() + off - 1;
        	} 
			else 
			{
	            throw std::ios::failure("bad seek direction");
    	    }

        	// Check for errors
	        if (next < 0 || next >= int(buf_.size()))
			{
    	        throw std::ios::failure("bad seek offset");
			}
    	    pos_ = next;
        	return pos_;
	    }

		ByteBuffer const & buffer() const { return buf_; }
		std::size_t const  & current_pos() const { return pos_; }

	private:
	    ByteBuffer const &  buf_;
    	std::size_t   pos_;
	};	

	typedef boost::iostreams::stream_buffer< 
				byte_buffer_stream_source< 
					char 
				> 
			> CharStreamByteBuffer;
	typedef boost::iostreams::stream_buffer< 
				byte_buffer_stream_source< 
					Byte 
				> 
			> ByteStreamByteBuffer;
}

#endif //GUARD_LIBOMVTK_NETWORK_HTTP_BYTE_BUFFER_STREAM_SOURCE_H

