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
#ifndef GUARD_OMVTK_NETWORK_HTTP_DETAIL_DEFAULT_SETTINGS_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_DETAIL_DEFAULT_SETTINGS_INCLUDED

#include "../../libomvtk/types/base_types.h"
#include "../http_header.h"

namespace omvtk {
    namespace http {
        namespace detail {
            /// Defines default settings for all requests 
            /// which have no specialization
            template < typename MethodType > 
            struct request_default_settings {
                struct apply {
                    template<typename RequestType>
                    apply( RequestType & ){} 
                };
            };

            /// Defines default settings for POST requests
            /// So far we're by default setting 
            /// Content-Type: application/x-www-form-urlencoded
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
    }
}

#endif //GUARD_OMVTK_NETWORK_HTTP_TRAITS_VERSION_TRAITS_H_INCLUDED
