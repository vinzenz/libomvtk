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
#ifndef GUARD_LIBOMVTK_HTTP_HTTP_REQUEST_BUILDER_H_INCLUDED
#define GUARD_LIBOMVTK_HTTP_HTTP_REQUEST_BUILDER_H_INCLUDED
#include <sstream>
#include <boost/foreach.hpp>
#include "http_headers.h"

namespace omvtk {

    template< typename DataType > 
    struct HTTPRequestBuilder {

        String operator()( DataType const & r ){
            std::ostringstream m;
            m << r.method_ << " "; path(r, m); m << " HTTP/1.1\r\n";
            host(r, m);
            headers( r, m );
            m << "\r\n";
            m << r.body_;
            return m.str();
        };

        void headers( DataType const & r, std::ostream & os ) {
            typedef std::pair<String,String> value_type;
            BOOST_FOREACH( value_type const & value,  r.headers_ ) {
                os << value.first << ": " << value.second << "\r\n";
            }
        }

        void host( DataType const & r, std::ostream & m) {
            m << "Host: " << r.uri_.get().authority().host();
            m << "\r\n";
        }

        void path( DataType const & r, std::ostream & m) {

            if ( r.uri_.get().path().empty() ) {
                m << "/";
            }
            else {
                m << r.uri_.get().path(); 
            }

            if ( !r.uri_.get().query().empty() ) {
                m << "?" << r.uri_.get().query();
            }

            if ( !r.uri_.get().fragment().empty() ) {
                    m << "#" << r.uri_.get().fragment();
            }        
        }
    };
}

#endif //GUARD_LIBOMVTK_HTTP_HTTP_REQUEST_BUILDER_H_INCLUDED
