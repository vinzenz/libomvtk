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
#ifndef GUARD_OMVTK_NETWORK_HTTP_TRAITS_URL_TRAITS_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_TRAITS_URL_TRAITS_H_INCLUDED

#include "../../libomvtk/types/base_types.h"

namespace omvtk {
    namespace http {
        namespace detail {

            /// Simple type which holds the URL and returns the value of it
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
        }

        /// Defines the URL traits
        template< typename Tag >
        struct url_traits {
            typedef detail::url_fragment<String> type;
        };            
    }
}

#endif //GUARD_OMVTK_NETWORK_HTTP_TRAITS_URL_TRAITS_H_INCLUDED
