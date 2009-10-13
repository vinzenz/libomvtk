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
#ifndef GUARD_LIBOMVTK_UTILS_HEX_STRING_H_INCLUDED
#define GUARD_LIBOMVTK_UTILS_HEX_STRING_H_INCLUDED

#include "../types/sub_range.h"
#include <boost/foreach.hpp>

namespace omvtk {

    template< typename IteratorT >
    String to_hex_string( IteratorT begin, IteratorT end ) {
        return to_hex_string( byte_sub_range( begin, end ) );
    }

    String to_hex_string( byte_sub_range const & range ) {
        static char const HEX_C[17] = "0123456789abcdef";
        String result;
        BOOST_FOREACH( Byte b, range )
        {
            result += HEX_C[ (b & 0xF0) >> 4 ];
            result += HEX_C[ (b & 0x0F) ];
        }
        return result;
    }
}

#endif //GUARD_LIBOMVTK_UTILS_HEX_STRING_H_INCLUDED