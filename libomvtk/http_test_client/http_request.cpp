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
#include "http_request.h"
namespace omvtk
{
    using http::ContentType;
    using http::ContentLength;


    HTTPRequest::HTTPRequest( LLURI const & uri )
    : data_( uri, "GET", String() )
    {
    }        

    HTTPRequest::HTTPRequest( LLURI const & uri, String const & body )
    : data_( uri, "POST", body )
    {
        header() %  http::ContentLength( body.size() )
                 %  http::ContentType( "application/x-www-form-urlencoded" );
    }

    HTTPRequest::HTTPRequest( LLURI const & uri, String const & body, String const & content_type )
    : data_( uri, "POST", body )
    {
        header() %  http::ContentLength( body.size() )
                 %  http::ContentType( content_type );
    }
    
    HTTPRequest::HTTPRequest( HTTPRequest const & o ) 
    : data_( o.data_ )
    {}

    HTTPRequest & HTTPRequest::operator=( HTTPRequest o ) {
        swap( o );
        return *this;
    }

    void HTTPRequest::swap( HTTPRequest & o ) {
        data_.swap( o.data_ );
    }

    http::HeaderProxy HTTPRequest::header() {
        return http::HeaderProxy( boost::ref( data_.headers_ ) );
    }

    http::ConstHeaderProxy const HTTPRequest::header() const {
        return http::ConstHeaderProxy( boost::ref( data_.headers_ ) );
    }

    bool HTTPRequest::ssl() const {
        return data_.uri_.get().scheme().string() == "https";
    }

    String HTTPRequest::to_string() const {
        return Builder()(data_);
    }    

    LLUUID const & HTTPRequest::id() const {
        return data_.id_;
    }
    
    String const & HTTPRequest::method() const {
        return data_.method_;
    }

    String const & HTTPRequest::body() const {
        return data_.body_;
    }

    HTTPRequest::Data::Data( LLURI const & uri, String const & method, String const & body  ) 
    : id_( LLUUID::random() )
    , uri_( uri )
    , method_( method )
    , body_( body )
    , headers_()
    {}

    void HTTPRequest::Data::swap( Data & o ) {
        id_.swap( o.id_ );
        uri_.swap( o.uri_ );
        method_.swap( o.method_ );
        body_.swap( o.body_ );
        headers_.swap( o.headers_ );
    }

}

