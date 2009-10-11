#include <iostream>
#include <boost/lexical_cast.hpp>
#include <net/http/detail/tags.hpp>
#include <net/http/response/basic_response.hpp>
#include <net/client/client.hpp>
#include "../libomvtk/logger/logger.h"
#include "../libomvtk/types/lluri.h"
#include "../libomvtk/types/lluuid.h"
#include "../libomvtk/utils/md5.h"
#include "../libomvtk/gridclient.h"
#include <boost/optional.hpp>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

typedef net::basic_client<net::http::message_tag>           tcp_client;
typedef net::http::basic_response<net::http::message_tag>   http_response_base;

omvtk::LLUUID random_uuid(){
    return boost::uuids::random_generator<>()();
}

using omvtk::Network;

#if 0
struct Network{

    Network()
        : service_()
        , context_(service_, boost::asio::ssl::context::sslv23)
    {}

    boost::asio::io_service & service(){ return service_; }
    boost::asio::ssl::context & context(){ return context_; }

protected:
    boost::asio::io_service service_;
    boost::asio::ssl::context context_;
};
#endif

struct HTTPRequest {
    typedef boost::unordered_multimap< omvtk::String, omvtk::String >  HeaderCollection;
    HTTPRequest()
        : id( random_uuid() )
        , uri()
        , method()
        , body() 
        , headers() {
    }

    omvtk::LLUUID       id;
    omvtk::LLURI        uri;
    omvtk::String       method;
    omvtk::String       body;    
    HeaderCollection    headers;
};

struct HTTPResponse : http_response_base {
    
};

struct HTTPRequestBuilder {
    omvtk::String operator()(HTTPRequest const  & r){
        std::ostringstream m;
        m << r.method << " "; path(r, m); m << " HTTP/1.1\r\n";
        host(r, m);
        headers( r, m );
        m << "\r\n";
        m << r.body;
        return m.str();
    };

    void headers( HTTPRequest const & r, std::ostream & os ) {
        BOOST_FOREACH( HTTPRequest::HeaderCollection::value_type const & value,  r.headers ) {
            os << value.first << ": " << value.second << "\r\n";
        }
    }

    void host(HTTPRequest const & r, std::ostream & m) {
        m << "Host: " << r.uri.get().authority().host();
        if ( r.uri.get().authority().port() ){
            m << ":" << r.uri.get().authority().port();
        }
        m << "\r\n";
    }

    void path(HTTPRequest const & r, std::ostream & m) {

        if ( r.uri.get().path().empty() ) {
            m << "/";
        }
        else {
            m << r.uri.get().path(); 
        }

        if ( !r.uri.get().query().empty() ) {
            m << "?" << r.uri.get().query();
        }

        if ( !r.uri.get().fragment().empty() ) {
                m << "#" << r.uri.get().fragment();
        }        
    }
};

struct HttpClient {
    struct Progress {
        enum State {
            Connecting,
            Connected,        
            RequestSent,
            HeadersReceived,
            BodyInTransfer,
            Finished
        };

        omvtk::String to_string() const {
            switch( state ) {
            case Connecting:        return "Connecting";
            case Connected:         return "Connected";
            case RequestSent:       return "RequestSent";
            case HeadersReceived:   return "HeadersReceived";
            case BodyInTransfer:    return "BodyInTransfer";
            case Finished:          return "Finished";
            }
            return "Unknown";
        }
        
        Progress()
            : state( Connecting )
            , error_code()
            , bytes_sent( 0 )
            , bytes_received( 0 )
            , response( )
        {}

        State                       state;
        boost::system::error_code   error_code;
        omvtk::UInt64               bytes_sent;
        omvtk::UInt64               bytes_received;
        HTTPResponse                response;
    };

    typedef boost::function< bool (HTTPRequest const & request, Progress const & data) > ProgressHandler;
    struct Instance {
        Instance(Network & network, 
                 HTTPRequest const & r = HTTPRequest(), 
                 ProgressHandler const & handler = ProgressHandler() )
        : client( network.service() ) //, network.context() )
        , request(r)
        , handler(handler) {
        }

        tcp_client      client;
        HTTPRequest     request;
        Progress        progress;
        ProgressHandler handler;
    };
    typedef HTTPRequest::HeaderCollection HeaderCollection;
    typedef boost::shared_ptr<Instance> InstancePtr;

    HttpClient(Network & network)
        : network_(network) {
    }

    omvtk::LLUUID get(omvtk::LLURI const & uri, ProgressHandler handler, 
             HeaderCollection const & headers = HeaderCollection()) {

        return create_instance("GET", uri, omvtk::String(), handler, headers);

    }

    omvtk::LLUUID post(omvtk::LLURI const & uri, omvtk::String const & body, 
              ProgressHandler handler, HeaderCollection const & headers = HeaderCollection()) {
        
        return create_instance( "POST", uri, body, handler, headers );
    }

    omvtk::LLUUID post(omvtk::LLURI const & uri, omvtk::String const & content_type, 
              omvtk::String const & body, ProgressHandler handler) {

        HeaderCollection headers;
        headers.insert( std::make_pair( "Content-Type", content_type ) );
        return post( uri, body, handler, headers );
        
    }

    omvtk::LLUUID create_instance(omvtk::String const & method, omvtk::LLURI const & uri, 
                         omvtk::String const & body, ProgressHandler handler, 
                         HeaderCollection const & headers) {

        InstancePtr instance(new Instance(network_));
        instance->request.uri                       = uri;
        instance->request.method                    = method;
        instance->request.body                      = body;
        instance->request.headers                   = headers;
        
        initiate_instance(instance);

        return instance->request.id;
    }

    void initiate_instance(InstancePtr instance) {

        LOG_APP << "Instance initiated to: " << instance->request.uri 
                << " method: "               << instance->request.method
                << " request id: "           << instance->request.id;

        instance->client.async_connect( instance->request.uri.get().authority().host(), 
                                        boost::lexical_cast<omvtk::String>( instance->request.uri.get().authority().port() ), 
                                        boost::bind( &HttpClient::on_connected, this, _1, instance ) 
                                      );
    }

    void on_connected( boost::system::error_code const & ec, InstancePtr instance ) {
        instance->progress.error_code = ec;
        if(!ec) {
            LOG_APP << "Request id: " << instance->request.id << " Server connection established";
            instance->progress.state = Progress::Connected;            
            if( !progress( instance ) ) {
                return;
            }

            omvtk::String message = HTTPRequestBuilder()(instance->request);
            LOG_DBG << "Sending Message:\n----------------------\n" << message << "\n----------------------------\n";            

            boost::asio::async_write( instance->client.socket(), 
                                      boost::asio::buffer( message ), 
                                      boost::bind( &HttpClient::on_request_sent, this, _1, _2, instance )
                                    );
        }
        else {
            LOG_ERR << "Request id: "   << instance->request.id
                    << " Failure: Couldn't establish connection to server "
                    << " URI: "         << instance->request.uri
                    << " Method: "      << instance->request.uri
                    << " Error Code: "  << ec 
                    << " Message: "     << ec.message();
            progress( instance );
        }        
    }

    bool progress( InstancePtr instance ) {
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
    
    void on_request_sent( boost::system::error_code const & ec, size_t transfered, InstancePtr instance ) {
        instance->progress.error_code = ec;
        instance->progress.bytes_sent += transfered;
        if( !ec ) {
            instance->progress.state = Progress::RequestSent;
            LOG_APP << "Request id: " << instance->request.id << " Request sent.";
            if( !progress( instance ) ) {
                return;
            }
        }
        else {
            LOG_ERR << "Request id: "   << instance->request.id
                    << " Failure: Failed sending HTTP request"
                    << " URI: "         << instance->request.uri
                    << " Method: "      << instance->request.uri
                    << " Error Code: "  << ec 
                    << " Message: "     << ec.message();
            progress( instance );
        }
    }

protected:
    Network & network_;
};

int main()
{
    omvtk::logger::set_log_level(omvtk::logger::debug);
    omvtk::GridClient grid;
    HttpClient client(grid.network());

    client.post(omvtk::LLURI("http://www.google.com"), "application/omvtk", "", HttpClient::ProgressHandler());
    grid.network().service().run();
}