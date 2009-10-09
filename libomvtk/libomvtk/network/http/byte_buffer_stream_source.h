// vim:et:st=4:ts=4:sts=4:
// Copyright (c) 2008,2009 by the OpenMetaverse Toolkit Library Team
// All rights reserved.
//
// - Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Neither the name of the OpenMetaverse Toolkit Library Team nor the names
//   of its contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE
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

