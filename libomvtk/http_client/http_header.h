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
#ifndef GUARD_OMVTK_NETWORK_HTTP_HTTP_HEADER_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_HTTP_HEADER_H_INCLUDED

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/unordered_map.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/ref.hpp>

#include <utility>

namespace omvtk {
    namespace http {
        
        struct Header : std::pair< String, String >{
            typedef boost::unordered_multimap< String, String > collection_type;
            
            Header()
            : std::pair<String, String>()
            {}

            Header( String const & name, String const & value )
            : std::pair<String, String>(name, value)
            {}
            
            Header( Header const & o )
            : std::pair<String, String>(o)
            {}
            
            Header & operator=( Header o ) {
                swap( o );
                return *this;
            }

            void swap( Header & o ) {
                first.swap( o.first );
                second.swap( o.second );
            }

            String & name() { 
                return first; 
            }
            
            String const & name() const { 
                return first; 
            }

            String & value() { 
                return second; 
            }
            
            String const & value() const { 
                return second; 
            }

            /// Apply single is used to ensure that certain headers
            /// Only appear once in the headers
            void apply_single( collection_type & collection ) const {
                collection_type::iterator it = collection.find( name() );
                if ( it == collection.end() ) {
                    collection.insert( *this );
                }
                else {
                    it->second = value();
                }
            }
            
            void apply( collection_type & collection ) const {
                collection.insert( *this );
            }
        };
        
        inline void swap ( Header & a, Header & b ) {
            a.swap( b );
        }
        
        struct Connection : Header {
            Connection( String const & value ) 
            : Header( "Connection", value )
            {}
            
            void apply( collection_type & collection ) const {
                apply_single( collection );
            }
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

            void apply( collection_type & collection ) const {
                apply_single( collection );
            }
        };

        struct ContentType : Header {
            ContentType( String const & value )
            : Header( "Content-Type", value ) 
            {}

            void apply( collection_type & collection ) const {
                apply_single( collection );
            }
        };
        
        template < typename HeaderCollectionType >
        struct basic_header_proxy {
            typedef boost::reference_wrapper<HeaderCollectionType> collection_reference;
            typedef HeaderCollectionType collection_type;

            basic_header_proxy( collection_reference collection )
            : collection_( collection ) 
            {}

            basic_header_proxy( basic_header_proxy const & o )
            : collection_(o.collection_) 
            {}

            basic_header_proxy & operator=( basic_header_proxy o ) {
                std::swap( collection_, o.collection_ );
                return *this;
            }

            template< typename T >
            struct enable_if_header 
            : boost::enable_if< boost::is_base_and_derived< Header, T >, T > {
            };

            template< typename HeaderType >
            basic_header_proxy & operator % ( typename enable_if_header<HeaderType>::type const & header ) {
                header.apply( collection_.get() );
                return *this;
            }

            typename boost::add_const<collection_type>::type & headers() const 
            {
                return collection_.get();
            }

            collection_type & headers()
            {
                return collection_.get();
            }

        protected:
            collection_reference collection_;
        };

        typedef basic_header_proxy< Header::collection_type > HeaderProxy;
        typedef basic_header_proxy< Header::collection_type const > ConstHeaderProxy;        
    }
}

#endif //GUARD_OMVTK_NETWORK_HTTP_HTTP_HEADER_H_INCLUDED
