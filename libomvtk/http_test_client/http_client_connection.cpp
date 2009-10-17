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

#include "http_client_connection.h"
#include "../libomvtk/library.h"
#include "../libomvtk/logger/logger.h"

namespace omvtk {
    HTTPClientConnection::Progress::Progress() 
    : state(Connecting)
    , error_code()
    , bytes_sent()
    , bytes_received()
    {}   

    char const * HTTPClientConnection::Progress::to_string() const {
        switch( state ) {
            case Connecting:        return "Connecting";
            case Connected:         return "Connected";
            case RequestSent:       return "RequestSent";
            case HeadersInTransfer: return "HeadersInTransfer";
            case HeadersReceived:   return "HeadersReceived";
            case BodyInTransfer:    return "BodyInTransfer";
            case Finished:          return "Finished";
            default:
                break;
        }
        return "Unknown";
    }
 
    HTTPClientConnection::HTTPClientConnection( ProgressHandler handler, bool ssl )
    : library_()
    , connection_( library_.service(), library_.context(), ssl )
    , progress_()
    , response_()
    , buffer_()
    , handler_( handler )
    , host_()
    , port_()
    , endpoint_()
    , request_()
    , header_parser_()
    , chunked_parser_()
    {}

    void HTTPClientConnection::start( String const & host, UInt16 port, String const & request) {
        host_ = host;
        port_ = port;
        request_ = request;
        progress_ = Progress();
        connection_.async_connect( 
            host, 
            boost::lexical_cast< String >( port ), 
            boost::bind( &HTTPClientConnection::on_connected, this, _1 ) 
        );
        progress();
    }

    void HTTPClientConnection::send_request( ) {
        boost::asio::async_write( 
            connection_.socket(), 
            boost::asio::buffer( request_ ), 
            boost::bind( &HTTPClientConnection::on_request_sent, this, _1, _2 )
        );
    }

    void HTTPClientConnection::read_response() {
        connection_.socket().async_read_some( 
            boost::asio::buffer( buffer_ ), 
            boost::bind( &HTTPClientConnection::on_data_received, this, _1, _2 )
        );
    }

    bool HTTPClientConnection::progress() {        
        switch( progress_.state ){
        case Progress::Connecting:
            {
                LOG_INFO << "[HTTPClient] Attempt to connect to " << host_ << ":" << port_;
            }
            break;
        case Progress::Connected:       
            {
                LOG_INFO << "[HTTPClient] Connected to " << host_ << ":" << port_ << "[" << endpoint_ << "]";
                send_request( ); //"GET / HTTP/1.1\r\nHost: www.google.cz\r\nConnection: Close\r\n\r\n" );
            }
            break;
        case Progress::RequestSent:
            {
                LOG_INFO << "[HTTPClient] Request sent to " << host_ << ":" << port_ << "[" << endpoint_ << "]";
                read_response();
            }
            break;
        case Progress::HeadersInTransfer:
            {
                LOG_INFO << "[HTTPClient] Headers from  " << host_ << ":" << port_ << "[" << endpoint_ << "] still in transfer";                
                read_response();
            }
            break;
        case Progress::HeadersReceived:
            {
                LOG_INFO << "[HTTPClient] Headers from  " << host_ << ":" << port_ << "[" << endpoint_ << "] received";
                read_response();
            }
            break;
        case Progress::BodyInTransfer:
            {
                LOG_INFO << "[HTTPClient] Body from  " << host_ << ":" << port_ << "[" << endpoint_ << "] in transfer";
                read_response();
            }
            break;
        case Progress::Finished:
            {
                LOG_INFO << "[HTTPClient] Body from  " << host_ << ":" << port_ << "[" << endpoint_ << "] transfered";
            }
            break;
        default:
            {
                LOG_ERR << "Unknown HTTPClientConnection::Progress state reached aborting"; 
                return false; 
            }        
        }
        return true;
    }

    void HTTPClientConnection::on_connected( ErrorCode ec ) {        
        endpoint_ = connection_.socket().base().get_plain_socket().remote_endpoint();
        progress_.error_code = ec;
        if ( !ec ) {
            progress_.state = Progress::Connected;
        }
        progress();
    }

    void HTTPClientConnection::on_request_sent( ErrorCode ec, size_t transfered ) {
        progress_.error_code = ec;
        if ( !ec ) {
            progress_.state = Progress::RequestSent;
            progress_.bytes_sent += transfered;
            progress();
        }
    }

    void HTTPClientConnection::on_data_received( ErrorCode ec, size_t transfered ) {
        progress_.error_code = ec;

        if ( transfered ) {

            Buffer::const_iterator iter = buffer_.begin();
            Buffer::const_iterator end = buffer_.begin() + transfered;
            boost::tribool parse_result = false;

            switch( progress_.state ){
            case Progress::RequestSent:
                progress_.state = Progress::HeadersInTransfer;
            case Progress::HeadersInTransfer:
                parse_result = header_parser_.parse( iter, end, response_ );
                if ( !parse_result ) {
                    std::cout << "Parse error" << std::endl;
                    return;
                }
                else if ( parse_result == boost::indeterminate ) {
                    std::cout << "Headers still not finished" << std::endl;
                    // reschedule read or report error
                    break;
                }                
                progress_.state = Progress::HeadersReceived;
            case Progress::HeadersReceived:
                progress_.state = Progress::BodyInTransfer;
            case Progress::BodyInTransfer:
                std::cout << "[[[[" << String(iter, end) << "]]]]" << std::endl;
                break;
            case Progress::Finished:                
                break;
            default:
                LOG_ERR << "Invalid state: " << progress_.to_string() 
                        << " while connected to endpoint: " << host_ << ":" << port_ 
                        << "[" << endpoint_ << "]";
                break;
            }            
        }

        if ( !ec ) {
            progress();
        }
        // Those error codes are only ok if we have BodyInTransfer
        else if ( progress_.state == Progress::BodyInTransfer 
             && ( ec == boost::asio::error::eof || ec == boost::asio::error::shut_down ) ) {
            progress_.state = Progress::Finished;
            progress();
        }
        else {
            std::cout << "ErrorCode: " << ec << " + Transfered: " << transfered 
                      << " ErrorMessage: " << ec.message() << std::endl;
        }
        // TODO: Proper handling
    }
}

