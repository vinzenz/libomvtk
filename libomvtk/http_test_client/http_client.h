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
#ifndef GUARD_OMVTK_NETWORK_HTTP_HTTP_CLIENT_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_HTTP_CLIENT_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "../libomvtk/types/lluri.h"
#include "../libomvtk/types/lluuid.h"
#include "../libomvtk/types/error.h"
#include "http_request.h"
#include "http_response.h"

namespace omvtk{
    struct Network;
    struct HttpClient {
        struct Progress {
            enum State {
                Connecting,
                Connected,        
                RequestSent,
                HeadersInTransfer,
                HeadersReceived,
                BodyInTransfer,
                Finished
            };

            String to_string() const;
            Progress();
            State                       state;
            ErrorCode   error_code;
            UInt64               bytes_sent;
            UInt64               bytes_received;
            HTTPResponse                response;
        };

        typedef boost::function< bool (HTTPRequest const & request, Progress const & data) > ProgressHandler;
        typedef HTTPRequest::HeaderCollection HeaderCollection;

        HttpClient(Network & network);
        LLUUID get(LLURI const & uri, ProgressHandler handler, 
                 HeaderCollection const & headers = HeaderCollection());
        
        LLUUID post(LLURI const & uri, String const & body, 
                  ProgressHandler handler, HeaderCollection const & headers = HeaderCollection());
        
        LLUUID post(LLURI const & uri, String const & content_type, 
                  String const & body, ProgressHandler handler);

        LLUUID create_instance(String const & method, LLURI const & uri, 
                             String const & body, ProgressHandler handler, 
                             HeaderCollection const & headers);

    protected:
        struct Instance;
        typedef boost::shared_ptr<Instance> InstancePtr;

    protected:
        void initiate_instance(InstancePtr instance);
        void on_connected( ErrorCode const & ec, InstancePtr instance );
        bool progress( InstancePtr instance );
        void on_request_sent( ErrorCode const & ec, size_t transfered, InstancePtr instance );

        typedef void (HttpClient::*ReadTargetPtr)(ErrorCode, size_t, InstancePtr);
        void schedule_next_read( ReadTargetPtr ptr, InstancePtr instance, bool headersOnly = false );
        
        void on_headers_received( ErrorCode ec, size_t transfered, InstancePtr instance );
        void on_body_received( ErrorCode ec, size_t transfered, InstancePtr instance );
        void scan_header( ErrorCode ec, size_t transfered, InstancePtr instance );
        void scan_body( ErrorCode ec, size_t transfered, InstancePtr instance, std::ptrdiff_t off );
        void scan_chunked_body( ErrorCode ec, size_t transfered, InstancePtr instance, std::ptrdiff_t off );
    protected:
        Network & network_;
    };

}

#endif //GUARD_OMVTK_NETWORK_HTTP_HTTP_CLIENT_H_INCLUDED
