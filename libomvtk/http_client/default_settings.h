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
#ifndef GUARD_OMVTK_NETWORK_HTTP_DEFAULT_SETTINGS_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_DEFAULT_SETTINGS_H_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/function_types/result_type.hpp>

#include "detail/default_settings.h"

namespace omvtk {
    namespace http {

        // Forward declarations
        template< typename Tag >
        struct basic_request;
        
        template< typename Tag >
        struct basic_response;

        /// Base template for default settings 
        /// to match all unmatched specializations
        /// And allow them to be handled gracefully
        template < typename > 
        struct default_settings {
            struct apply {
                template<typename T>
                apply( T & )
                {} 
            };
        };

        /// Settings for all basic_response types
        template< typename Tag >
        struct response_settings {
            static void apply( basic_response< Tag > & ){
            }            
        };

        /// Settings for all basic_request types
        template< typename Tag >
        struct request_settings {
            static void apply( basic_request< Tag > & ){
            }
        };

        /// Overload to identify the right default settings for a 
        /// certain tag used for basic_request
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

        /// Overload to identify the right default settings for a 
        /// certain tag used for basic_response
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

        /// Applies the default settings according the method and the class used
        template< typename MethodType, typename Tag >
        void apply_default_settings( MethodType, basic_request<Tag> & request ) {
            typename detail::request_default_settings < 
                    typename boost::function_types::result_type< MethodType >::type 
                >::apply a_( request );
            typename default_settings< basic_request<Tag> >::apply a2_( request );
        }
    }
}

#endif //GUARD_OMVTK_NETWORK_HTTP_DEFAULT_SETTINGS_H_INCLUDED
