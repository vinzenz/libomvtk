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
#ifndef GUARD_OMVTK_NETWORK_HTTP_HTTP_REQUEST_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_HTTP_REQUEST_H_INCLUDED

#include "http_headers.h"
#include "../libomvtk/types/lluuid.h"
#include "../libomvtk/types/lluri.h"
#include "http_request_builder.h"

namespace omvtk {

    struct HTTPRequest {
        typedef http::Header::Collection HeaderCollectionType;

        HTTPRequest( LLURI const & uri );
        HTTPRequest( LLURI const & uri, String const & body );
        HTTPRequest( LLURI const & uri, String const & body, String const & content_type );
        HTTPRequest( HTTPRequest const & o );

        HTTPRequest & operator=( HTTPRequest o );
        void swap( HTTPRequest & o );
        
        http::HeaderProxy header();
        http::ConstHeaderProxy const header() const;

        bool ssl() const;
        String to_string() const;
        
        LLUUID const & id() const;
        String const & method() const;
        String const & body() const;
    protected:
        struct Data {
            Data( LLURI const & uri, String const & method, String const & body  );
            LLUUID                 id_;
            LLURI                  uri_;
            String                 method_;
            String                 body_;
            HeaderCollectionType   headers_;
            void swap( Data & o );
        };
        typedef HTTPRequestBuilder<Data> Builder;
    protected:
        Data data_;
    };
}

#endif // GUARD_OMVTK_NETWORK_HTTP_HTTP_REQUEST_H_INCLUDED
