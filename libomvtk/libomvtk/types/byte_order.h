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
