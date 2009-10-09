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

