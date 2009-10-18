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
#ifndef GUARD_OMVTK_NETWORK_HTTP_HTTP_CLIENT_CONNECTION_H_INCLUDED
#define GUARD_OMVTK_NETWORK_HTTP_HTTP_CLIENT_CONNECTION_H_INCLUDED

#include "../libomvtk/library.h"
#include "http_request.h"
#include "http_response.h"
#include <net/client/client.hpp>
#include <net/http/parser/header_parser.hpp>
#include <net/http/parser/content_parser.hpp>
#include <net/client/client.hpp>
#include <istream>

namespace omvtk {    
    
    struct HTTPClientConnection {
        typedef net::http::basic_chunked_content_parser<net::http::message_tag> ChunkedParser;
        typedef net::http::basic_header_parser<net::http::message_tag, false>   HeaderParser;
        typedef net::basic_client<net::http::message_tag>   Connection;
        typedef boost::asio::ip::tcp::endpoint              Endpoint;
        typedef boost::system::error_code                   ErrorCode;
        typedef boost::array< char , 0x1000 >               Buffer;
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
            
            Progress();

            char const * to_string() const;
            
            State       state;
            ErrorCode   error_code;
            UInt64      bytes_sent;
            UInt64      bytes_received;
        };

        typedef boost::function< bool ( Progress const &, HTTPResponse const & ) > ProgressHandler;

        HTTPClientConnection( ProgressHandler handler, bool ssl = false );

        void start( String const & host, UInt16 port, String const & request );
        void send_request( );
        void read_response();

    protected:
        bool progress();

        void on_connected( ErrorCode ec );
        void on_request_sent( ErrorCode ec, size_t transfered );
        void on_data_received( ErrorCode ec, size_t transfered );

    protected:
        Library             library_;
        Connection          connection_;
        Progress            progress_;
        HTTPResponse        response_;
        Buffer              buffer_;
        ProgressHandler     handler_;
        String              host_;
        UInt16              port_;
        Endpoint            endpoint_;
        String              request_;
        HeaderParser        header_parser_;
        ChunkedParser       chunked_parser_;
    };

}

#endif //GUARD_OMVTK_NETWORK_HTTP_HTTP_CLIENT_CONNECTION_H_INCLUDED

