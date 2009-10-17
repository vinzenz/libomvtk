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
#ifndef GUARD_OMVTK_NETWORK_HTTP_HTTP_HEADERS_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_HTTP_HEADERS_H_INCLUDED

#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>
#include <boost/static_assert.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/add_const.hpp>

#include <utility>

#include "../libomvtk/types/base_types.h"

namespace omvtk {
    namespace http {

        struct Header : std::pair<String, String> {
            typedef boost::unordered_multimap< String, String > Collection;

            Header( String const & name, String const & value )
            : std::pair<String, String>( name, value ) 
            {}
        };

        struct Connection : Header {
            Connection( String const & value ) 
            : Header( "Connection", value )
            {}
        };

        struct Accept : Header {
            Accept( String const & value ) 
            : Header( "Accept", value ) 
            {}
        };

        struct ContentLength : Header {
            ContentLength( String const & value ) 
            : Header( "Content-Length", value )
            {}

            template< typename IntegralType >
            ContentLength( IntegralType value ) 
            : Header( "Content-Length", boost::lexical_cast<String>( value ) )
            {
                BOOST_STATIC_ASSERT( boost::is_integral<IntegralType>::value );
            }
        };

        struct ContentType : Header {
            ContentType( String const & value )
            : Header( "Content-Type", value ) 
            {}
        };
        
        template < typename HeaderCollectionType >
        struct HeaderProxyBase {
            typedef boost::reference_wrapper<HeaderCollectionType> CollectionRef;

            HeaderProxyBase( CollectionRef collection )
            : collection_( collection ) 
            {}

            HeaderProxyBase( HeaderProxyBase const & o )
            : collection_(o.collection_) 
            {}

            HeaderProxyBase & operator=( HeaderProxyBase o ) {
                std::swap( collection_, o.collection_ );
                return *this;
            }

            HeaderProxyBase & operator % ( Header const & header ) {
                collection_.get().insert( header );
                return *this;
            }

            typename boost::add_const<HeaderCollectionType>::type & get() const 
            {
                return collection_.get();
            }

            HeaderCollectionType & get()
            {
                return collection_.get();
            }

        protected:
            CollectionRef collection_;
        };

        typedef HeaderProxyBase< Header::Collection > HeaderProxy;
        typedef HeaderProxyBase< Header::Collection const > ConstHeaderProxy;
    }
}

#endif // GUARD_OMVTK_NETWORK_HTTP_HTTP_HEADERS_H_INCLUDED

