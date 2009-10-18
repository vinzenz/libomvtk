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
#ifndef GUARD_LIBOMVTK_TYPES_BASE_TYPES_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_BASE_TYPES_H_INCLUDED

#if _MSC_VER > 1200
#    pragma once
#endif

#include <string>
#include <vector>
#include <boost/range.hpp>
#include <boost/foreach.hpp>
#include <boost/cstdint.hpp>
#include <ostream>
#include <istream>

namespace omvtk
{
    typedef boost::int8_t  Int8;
    typedef boost::int16_t Int16;
    typedef boost::int32_t Int32;
    typedef boost::int64_t Int64;

    typedef boost::uint8_t  UInt8;
    typedef boost::uint16_t UInt16;
    typedef boost::uint32_t UInt32;
    typedef boost::uint64_t UInt64;

    typedef UInt8  Byte;
    typedef UInt16 Word;
    typedef UInt32 DWord;
    typedef UInt64 QWord;

    typedef float  Real32;
    typedef double Real64;

    typedef std::vector<Byte> ByteBuffer;

    typedef std::string  String;
    typedef std::string::value_type CharType;
    
#define OMVTK_TEXT( x ) x    

    template<typename RealT, typename IntT>
    struct RealTByteOrderHelper
    {

        union help
        {
            IntT i;
            RealT r;
        };

        static RealT convert(IntT (*f)(IntT), RealT r)
        {
            help h;
            h.r = r;
            h.i = f(h.i);
            return h.r;
        }
    };

    typedef RealTByteOrderHelper<Real64,UInt64> Real64ByteOrder; 
    typedef RealTByteOrderHelper<Real32,UInt32> Real32ByteOrder; 
}

namespace std
{
    inline std::ostream & operator<<(std::ostream & os, omvtk::ByteBuffer const & v)
    {
        BOOST_FOREACH(omvtk::Byte const & b, v)
        {
            os << (int(b));
        }
        return os;
    }
}

#endif //GUARD_LIBOMVTK_TYPES_BASE_TYPES_H_INCLUDED

