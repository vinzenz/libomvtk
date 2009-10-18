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
#ifndef GUARD_OMVTK_NETWORK_HTTP_HTTP_REQUEST_STREAM_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_HTTP_REQUEST_STREAM_H_INCLUDED

#include <boost/function_types/result_type.hpp>
#include <boost/asio.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <sstream>
#include <iostream>

#include "../libomvtk/types/base_types.h"
#include "http_header.h"

namespace omvtk {
    namespace http {
        namespace detail {
            template < typename MethodType > 
            struct request_default_settings {
                struct apply {
                    template<typename RequestType>
                    apply( RequestType & ){} 
                };
            };
                
            template <> 
            struct request_default_settings< method::detail::post > {
                struct apply {
                    template<typename RequestType>
                    apply( RequestType & r ){
                        r % ContentType( OMVTK_TEXT( "application/x-www-form-urlencoded" ) );
                    } 
                };
            };
        }
        
        template < typename > 
        struct default_settings {
            struct apply {
                template<typename T>
                apply( T & ){  std::cout << "Generic" << std::endl; } 
            };
        };
        
        template< typename Tag >
        struct basic_request;
        template< typename Tag >
        struct basic_response;

        template< typename Tag >
        struct     response_settings {
            static void apply( basic_response< Tag > & ){
                std::cout << "Setting response settings" << std::endl;
            }            
        };
        
        template< typename Tag >
        struct     request_settings {
            static void apply( basic_request< Tag > & ){
                std::cout << "Setting request settings" << std::endl;
            }
        };
        
        template < typename Tag > 
        struct default_settings< basic_request< Tag > >
        {
            struct apply {
                template<typename RequestType>
                apply( RequestType & r ){
                    request_settings< Tag >::apply( r );
                } 
            };
        };
        
        template < typename Tag > 
        struct default_settings< basic_response< Tag > >
        {
            struct apply {
                template<typename ResponseType>
                apply( ResponseType &  r ){
                    response_settings< Tag >::apply( r );
                } 
            };
        };

        
        template< typename MethodType, typename RequestType >
        void apply_default_settings( MethodType, RequestType & request ) {
            typename detail::request_default_settings < 
                    typename boost::function_types::result_type< MethodType >::type 
                >::apply a_( request );
            typename default_settings< RequestType >::apply a2_( request );
        }
        
        namespace version {
            struct http_1_1 {
                static CharType const * version() {
                    return OMVTK_TEXT( "1.1" );
                };
            };

            struct http_1_0 {
                static CharType const * version() {
                    return OMVTK_TEXT( "1.0" );
                };
            };
        }
        

        
        template< typename >
        struct version_traits {
            typedef version::http_1_1 type;
        };
        


        template< typename URLType >
        struct url_fragment {
            typedef URLType value_type;
            
            url_fragment( value_type const  & url )
            : url_( url ) 
            {}
            
            value_type const & url() const {
                return url_;
            }
                
            value_type & url() {
                return url_;
            }
        protected:
            value_type url_;
        };
        
        template< typename Tag >
        struct url_traits {
            typedef url_fragment<String> type;
        };            
        
        template< typename Tag >
        struct request_stream_traits {            
            typedef std::stringstream type;
        };
        
        template
        < 
            typename Tag
        >
        struct basic_request
        : method_traits< Tag >::type
        , url_traits< Tag >::type
        , request_stream_traits< Tag >::type
        , header_traits< Tag >::type
        , version_traits< Tag >::type {
            
            typedef Tag                                            tag_type;
            typedef typename method_traits< Tag >::type         method_type;
            typedef typename url_traits< Tag >::type             url_type;
            typedef typename request_stream_traits< Tag >::type stream_type;
            typedef typename header_traits< Tag >::type         header_type;
            typedef typename version_traits< Tag >::type         version_type;
            
            template< typename MethodType >
            basic_request( typename url_type::value_type const & u, MethodType m )
            : method_type( m )
            , url_type( u )
            , stream_type() 
            , header_type()
            , version_type()
            {
                apply_default_settings( m, *this );
            }
            
            basic_request( typename url_type::value_type const & u )
            : method_type( method::get )
            , url_type( u )
            , stream_type() 
            , header_type()
            , version_type()
            {
                apply_default_settings( method::get, *this );
            }
            
            template< typename HeaderType >
            basic_request & operator % ( HeaderType const & h ) {
                h.apply( this->headers() );
                return *this;
            }
        };
        
    }
}

#endif // GUARD_OMVTK_NETWORK_HTTP_HTTP_REQUEST_STREAM_H_INCLUDED
