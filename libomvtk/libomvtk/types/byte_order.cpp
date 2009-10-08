#include "byte_order.h"

#ifndef OMVTK_BIG_ENDIAN

#define OMVTK_SWAP_16(value)  (((value >> 8) & 0x00FF) | ((value << 8) & 0xFF00))

#define OMVTK_SWAP_32(value)  (((value >> 24) & 0x000000FF) | ((value >> 8) & 0x0000FF00)| \
                              ((value << 8) & 0x00FF0000) | ((value << 24) & 0xFF000000))

#define OMVTK_SWAP_64(value)  ((OMVTK_SWAP_32(UInt32(value >> 32))) | \
                              (UInt64(OMVTK_SWAP_32(UInt32(value & 0xFFFFFFFF))) << 32))

#define omvtk_be16toh(value) OMVTK_SWAP_16(value)
#define omvtk_be32toh(value) OMVTK_SWAP_32(value)
#define omvtk_be64toh(value) OMVTK_SWAP_64(value)

#define omvtk_htobe16(value) OMVTK_SWAP_16(value)
#define omvtk_htobe32(value) OMVTK_SWAP_32(value)
#define omvtk_htobe64(value) OMVTK_SWAP_64(value)

#else

#define omvtk_be16toh(value) value
#define omvtk_be32toh(value) value
#define omvtk_be64toh(value) value
#define omvtk_htobe16(value) value
#define omvtk_htobe32(value) value
#define omvtk_htobe64(value) value

#endif

namespace omvtk
{
    UInt16  to_host(UInt16 value)
    {
        return omvtk_be16toh(value);
    }

    Int16   to_host(Int16 value)
    {
        return omvtk_be16toh(value);
    }

    UInt32  to_host(UInt32 value)
    {
        return omvtk_be32toh(value);
    }

    Int32   to_host(Int32 value)
    {
        return omvtk_be32toh(value);
    }

    UInt64  to_host(UInt64 value)
    {
        return omvtk_be64toh(value);
    }

    Int64   to_host(Int64 value)
    {
        return omvtk_be64toh(value);
    }

    UInt16  to_network(UInt16 value)
    {
        return omvtk_htobe16(value);
    }

    Int16   to_network(Int16 value)
    {
        return omvtk_htobe16(value);
    }

    UInt32  to_network(UInt32 value)
    {
        return omvtk_htobe32(value);
    }

    Int32   to_network(Int32 value)
    {
        return omvtk_htobe32(value);
    }


    UInt64  to_network(UInt64 value)
    {
        return omvtk_htobe64(value);
    }

    Int64   to_network(Int64 value)
    {
        return omvtk_htobe64(value);
    }

}

