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

#include "http_client.h"
#include "http_request_builder.h"
#include "../libomvtk/gridclient.h"
#include "../libomvtk/logger/logger.h"

#include <net/http/detail/tags.hpp>
#include <net/http/response/basic_response.hpp>
#include <net/http/parser/header_parser.hpp>
#include <net/http/parser/content_parser.hpp>
#include <net/client/client.hpp>

#include <boost/foreach.hpp>

#define OMVTK_LOG_HTTP_ERROR( EC, INSTANCE, MSG )       \
    LOG_ERR << "Request id: "   << INSTANCE->request.id \
        << " " << MSG                                   \
        << " URI: "         << INSTANCE->request.uri    \
        << " Method: "      << INSTANCE->request.uri    \
        << " Error Code: "  << EC                       \
        << " Message: "     << EC.message()             \
        /**/


namespace {

    typedef net::basic_client<net::http::message_tag>                         tcp_client;
    typedef net::http::basic_header_parser<net::http::message_tag, false>     http_header_parser;
    typedef net::http::basic_chunked_content_parser<net::http::message_tag>   http_content_parser;


    void dumpHeaders( omvtk::HTTPResponse const & response ){
        typedef net::header_collection_traits<net::http::message_tag>::type::value_type header_value;
        omvtk::String headers;
        BOOST_FOREACH( header_value const & v, response.headers() ) {
            headers += v.first + ": " + v.second + "\n";
        }
        LOG_DBG << "Received Headers:\n---------------------------------------\n" 
            << "Status Code:    " << response.status_code() << "\n"
            << "Status Message: " << response.status_message() << "\n"
            << "HTTP Version:   " << unsigned(response.version().first)
                           << "." << unsigned(response.version().second) << "\n\n"
            << headers << "\n---------------------------------------";
    }
}

//##############################################################################
namespace omvtk {
    String HttpClient::Progress::to_string() const {
        switch( state ) {
            case Connecting:        return "Connecting";
            case Connected:         return "Connected";
            case RequestSent:       return "RequestSent";
            case HeadersInTransfer: return "HeadersInTransfer";
            case HeadersReceived:   return "HeadersReceived";
            case BodyInTransfer:    return "BodyInTransfer";
            case Finished:          return "Finished";
        }
        return "Unknown";
    }
        
        
    HttpClient::Progress::Progress()
    : state( Connecting )
    , error_code()
    , bytes_sent( 0 )
    , bytes_received( 0 )
    , response()
    {}

    struct HttpClient::Instance {
        typedef boost::array< char, 0x1000 > BufferType;

        Instance(Network & network, 
                 HTTPRequest const & r, 
                 ProgressHandler const & handler)
        : client( network.service(), network.context(), r.uri.get().scheme().string() == "https" )
        , request(r)
        , handler(handler)
        , header_parser() 
        , content_parser() {
        }

        tcp_client              client;
        HTTPRequest             request;
        Progress                progress;
        ProgressHandler         handler;
        BufferType              buffer;
        http_header_parser      header_parser;
        http_content_parser     content_parser;
        String                  requestBuffer;        
    };

//##############################################################################
    HttpClient::HttpClient(Network & network)
        : network_(network) {
    }

//##############################################################################
    LLUUID HttpClient::get( LLURI const & uri, ProgressHandler handler, 
                            HeaderCollection const & headers ) {
        return create_instance("GET", uri, String(), handler, headers);
    }

//##############################################################################
    LLUUID HttpClient::post( LLURI const & uri, String const & body, 
                             ProgressHandler handler, HeaderCollection const & headers ) {
        return create_instance( "POST", uri, body, handler, headers );
    }

//##############################################################################
    LLUUID HttpClient::post( LLURI const & uri, String const & content_type, 
                             String const & body, ProgressHandler handler ) {
        HeaderCollection headers;
        headers.insert( std::make_pair( "Content-Type", content_type ) );
        return post( uri, body, handler, headers );        
    }

//##############################################################################
    LLUUID HttpClient::create_instance( String const & method, LLURI const & uri, 
                                        String const & body, ProgressHandler handler, 
                                        HeaderCollection const & headers ) {
        HTTPRequest request;
        request.uri       = uri;
        request.method    = method;
        request.body      = body;
        request.headers   = headers;        
        
        InstancePtr instance( new Instance( network_, request, handler ) );
        initiate_instance( instance );

        return instance->request.id;
    }

//##############################################################################
    void HttpClient::initiate_instance( InstancePtr instance ) {

        LOG_APP << "Instance initiated to: " << instance->request.uri 
                << " method: "               << instance->request.method
                << " request id: "           << instance->request.id;

        UInt16 port       = instance->request.uri.get().authority().port();
        String portString = boost::lexical_cast<String>( port );
        String targetHost = instance->request.uri.get().authority().host();

        instance->client.async_connect( targetHost, portString, 
            boost::bind( &HttpClient::on_connected, this, _1, instance ) 
        );
    }

//##############################################################################
    bool HttpClient::progress( InstancePtr instance ) {
        if ( instance->handler ) {
            if( !instance->handler( instance->request, instance->progress ) ) {
                LOG_INFO << "Request was aborted by handler. ID: " << instance->request.id 
                    << " URI: " << instance->request.id
                    << " State: " << instance->progress.to_string();                         
                return false;
            }
        }
        return true;
    }

//##############################################################################
    void HttpClient::on_connected( ErrorCode const & ec, InstancePtr instance ) {
        instance->progress.error_code = ec;

        if(!ec) {
            
            LOG_APP << "Request id: " << instance->request.id << " Server connection established";
            
            instance->progress.state = Progress::Connected;            
            
            if( !progress( instance ) ) {
                return;
            }

            instance->requestBuffer = HTTPRequestBuilder()(instance->request);

            LOG_TRACE   << "Sending Message:"
                        << "\n----------------------------\n" 
                        << instance->requestBuffer 
                        << "\n----------------------------\n";            

            // Scheduling write - result will be passed to on_request_sent
            boost::asio::async_write( 
                instance->client.socket(), 
                boost::asio::buffer( instance->requestBuffer ), 
                boost::bind ( 
                    &HttpClient::on_request_sent, 
                    this, _1, _2, instance 
                )
            );
        }
        else {
            OMVTK_LOG_HTTP_ERROR( ec, instance, "Failure: Couldn't establish connection to server");
            progress( instance );
        }        
    }

//##############################################################################
    void HttpClient::on_request_sent( ErrorCode const & ec, size_t transfered, InstancePtr instance ) {
        instance->progress.error_code = ec;
        instance->progress.bytes_sent += transfered;
        if( !ec ) {
            
            instance->progress.state = Progress::RequestSent;
            
            LOG_APP << "Request id: " << instance->request.id << " Request sent.";

            if( !progress( instance ) ) {
                return;
            }

            schedule_next_read( &HttpClient::on_headers_received, instance );
        }
        else {
            OMVTK_LOG_HTTP_ERROR( ec, instance, "Failure: Failed sending HTTP request");
            progress( instance );

        }
    }
    
//##############################################################################
    void HttpClient::on_headers_received( ErrorCode ec, size_t transfered, InstancePtr instance ) {

        instance->progress.error_code = ec;
        instance->progress.bytes_received += transfered;

        if( !ec || ( transfered != 0 && ec == ErrorCode(boost::asio::error::eof) ) ) {
            LOG_APP << "Request id: " << instance->request.id << "Received data: " << transfered << " Bytes";            

            scan_header( ec, transfered, instance );
        }
        else {
            OMVTK_LOG_HTTP_ERROR( ec, instance, "Failure: Failure while retrieving data");
            progress( instance );

        }
    }

//##############################################################################
    void HttpClient::on_body_received( ErrorCode ec, size_t transfered, InstancePtr instance ) {
        instance->progress.error_code = ec;
        instance->progress.bytes_received += transfered;
        if( !ec ) {
            LOG_APP << "Request id: " << instance->request.id << "Received data: " << transfered << " Bytes";

            scan_body( ec, transfered, instance, 0);
        }
        else {
            OMVTK_LOG_HTTP_ERROR( ec, instance, "Failure: Failure while retrieving data");
            progress( instance );
        }
    }

//##############################################################################
    void HttpClient::scan_header( ErrorCode ec, size_t transfered, InstancePtr instance ) {
        instance->progress.state = Progress::HeadersInTransfer;
        if( !progress( instance ) ) {
            return;
        }
        std::cout << String(instance->buffer.begin(), instance->buffer.begin() + transfered) << std::endl;

        Instance::BufferType::iterator iter = instance->buffer.begin();
        boost::tribool result = instance->header_parser.parse( 
            iter, instance->buffer.begin() + transfered, 
            instance->progress.response 
        );

        if ( result == true ) {
            instance->progress.state = Progress::HeadersReceived;
            if( !progress( instance ) ) {
                return; 
            }

            if( iter != instance->buffer.end() ){
                dumpHeaders(instance->progress.response);
                scan_body( ec, transfered, instance, transfered - ( iter - instance->buffer.begin() ) );
            }
            else {
                schedule_next_read( &HttpClient::on_body_received, instance );
            }
        }
        else if( result == boost::indeterminate && !ec ) {
            schedule_next_read( &HttpClient::on_headers_received, instance );
        }
        else {
            ErrorCode ec( error::InvalidOrCorruptedProtocol );
            OMVTK_LOG_HTTP_ERROR( ec, instance, "Failure: Failed sending HTTP request");
            progress( instance );
        }
    }

//##############################################################################
    void HttpClient::scan_body( ErrorCode ec, size_t transfered, InstancePtr instance, std::ptrdiff_t off ) {
        if( transfered > off ) {    
            std::cout << String(instance->buffer.begin() + off, instance->buffer.begin() + transfered) << std::endl;
        }
        if ( !ec ) {             
            schedule_next_read( &HttpClient::on_body_received, instance );
        }
    }

//##############################################################################
    void HttpClient::scan_chunked_body( ErrorCode ec, size_t transfered, InstancePtr instance, std::ptrdiff_t off ) {
        instance->progress.state = Progress::BodyInTransfer;
        if( !progress( instance ) ) {
            return;
        }

        Instance::BufferType::iterator iter = instance->buffer.begin() + off;
        boost::tribool result = instance->content_parser.parse( 
            iter, instance->buffer.begin() + transfered, 
            instance->progress.response
        );

        if( result == true ) {
            instance->progress.state = Progress::Finished;
            progress( instance );
        }
        else if( result == boost::indeterminate ) {
            schedule_next_read( &HttpClient::on_body_received, instance );
        }
        else {
            ErrorCode ec( error::InvalidOrCorruptedProtocol );
            OMVTK_LOG_HTTP_ERROR( ec, instance, "Failure: Failed sending HTTP request");
            progress( instance );
        }
    }

//##############################################################################
    bool isHTTPClose( HTTPResponse const & response ) {
        if ( response.headers().count("Connection") ) {
            return response.headers().find("Connection")->second == "close";
        }
        return false;
    }

//##############################################################################
   void HttpClient::schedule_next_read( ReadTargetPtr ptr, InstancePtr instance, bool headersOnly ) {
        if ( isHTTPClose( instance->progress.response ) ) {
            boost::asio::async_read( instance->client.socket(), 
                boost::asio::buffer( instance->buffer ),
                boost::asio::transfer_all(),
                boost::bind( ptr, this, _1, _2, instance )
            );
        }
        else {
            boost::asio::async_read( instance->client.socket(), 
                boost::asio::buffer( instance->buffer ),
                boost::asio::transfer_at_least(1),
                boost::bind( ptr, this, _1, _2, instance )
            );
        }
    }

//##############################################################################
}