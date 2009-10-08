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
}


#endif //GUARD_LIBOMVTK_TYPES_BYTE_SWAP_H_INCLUDED
