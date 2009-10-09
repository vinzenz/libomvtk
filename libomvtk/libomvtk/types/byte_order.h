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
#ifndef GUARD_LIBOMVTK_TYPES_BYTE_SWAP_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_BYTE_SWAP_H_INCLUDED

#if _MSC_VER > 1200
#       pragma once
#endif

#include "base_types.h"

namespace omvtk
{
    UInt16  to_host(UInt16 value);
    Int16   to_host(Int16 value);

    UInt32  to_host(UInt32 value);
    Int32   to_host(Int32 value);

    UInt64  to_host(UInt64 value);
    Int64   to_host(Int64 value);

    UInt16  to_network(UInt16 value);
    Int16   to_network(Int16 value);

    UInt32  to_network(UInt32 value);
    Int32   to_network(Int32 value);

    UInt64  to_network(UInt64 value);
    Int64   to_network(Int64 value);

    namespace detail {
        union Real64ConvHelper {
            Real64 r;
            UInt64 u;
        };
        union Real32ConvHelper {
            Real32 r;
            UInt32 u;
        };
    }

    inline Real32  to_host(Real32 value){
        detail::Real32ConvHelper c;
        c.r = value;
        c.u = to_host(c.u);
        return c.r;
    }    

    inline Real64  to_host(Real64 value){
        detail::Real64ConvHelper c;
        c.r = value;
        c.u = to_host(c.u);
        return c.r;
    }    

    inline Real32  to_network(Real32 value){
        detail::Real32ConvHelper c;
        c.r = value;
        c.u = to_network(c.u);
        return c.r;
    }    

    inline Real64  to_network(Real64 value){
        detail::Real64ConvHelper c;
        c.r = value;
        c.u = to_network(c.u);
        return c.r;
    }    
}


#endif //GUARD_LIBOMVTK_TYPES_BYTE_SWAP_H_INCLUDED
