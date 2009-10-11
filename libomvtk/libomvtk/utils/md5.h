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
#ifndef GUARD_LIBOMVTK_UTILS_MD5_H_INCLUDED
#define GUARD_LIBOMVTK_UTILS_MD5_H_INCLUDED

#include <openssl/md5.h>
#include <boost/array.hpp>
#include "../types/sub_range.h"
#include "../types/exceptions.h"
#include "hex_string.h"

namespace omvtk
{
    struct MD5 {
        struct Hash 
        {
            boost::array< Byte, 16 > value;

            Hash & operator=( Hash o ) {
                value.swap( o.value );
                return *this;
            }
            
            bool operator == ( Hash const & o ) const {
                return o.value == value;
            }

            bool operator != ( Hash const & o ) const {
                return o.value != value;
            }

            bool operator < ( Hash const & o ) const {
                return o.value < value;
            }

            bool operator <= ( Hash const & o ) const {
                return o.value <= value;
            }

            bool operator > ( Hash const & o ) const {
                return o.value > value;
            }

            bool operator >= ( Hash const & o ) const {
                return o.value >= value;
            }

            String to_string() const {
                return to_hex_string( value.begin(), value.end() );
            };
        };

        MD5() : finalized_(false), context_(), hash_() {
            reset();
        }

        Hash get() {
            if ( !finalized_ ) {
                MD5_Final( hash_.value.data(), &context_ );
                finalized_ = true;
            }
            return hash_;
        }

        void reset() {
            finalized_ = false;
            MD5_Init( &context_ );
        }

        void add( byte_sub_range const & sub_range ) {
            if ( finalized_ ) { 
                throw IllegalStateException("MD5 instance was already finalized. Cannot use add before reset.");
            }
            MD5_Update( &context_, boost::begin( sub_range ), sub_range.size() );
        }
        
        template < typename RangeT >
        void add( RangeT const & range ) {
            add( range.begin(), range.end() );
        }

        template<typename IteratorT>
        void add( IteratorT first, IteratorT end ) {
            add( omvtk::byte_sub_range( first, end ) );
        }

        template< typename IteratorT >
        static Hash hash( IteratorT begin, IteratorT end ) {
            MD5 m;
            m.add( begin, end );
            return m.get();
        }

        template < typename RangeT >
        static Hash hash( RangeT const & range ) {
            return hash( range.begin(), range.end() );
        }
    
    protected:
        bool finalized_;
        MD5_CTX context_;
        Hash hash_;
    };
}

#endif //GUARD_LIBOMVTK_UTILS_MD5_H_INCLUDED
