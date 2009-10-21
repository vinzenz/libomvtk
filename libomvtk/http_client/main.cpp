#include "http_request.h"
#include "response.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/concepts.hpp> 
#include "request_result.h"
using namespace omvtk::http;

template struct basic_request< void >;
template struct basic_response< void >;
template struct basic_request_result< void >;

typedef basic_request<void> http_request;
typedef basic_response<void> http_response;
typedef basic_request_result< void > http_request_result;


int main(){
    http_request request( "http://www.google.com", method::post );

    request % ContentLength( 0x1000 ) // Da muss ich noch automatisch die größe from stream nehmen :-)
            % Accept( "*/*" )
            % ContentType( "application/llsd+xml" );

    std::cout << request.url()         << std::endl;
    std::cout << request.version()     << std::endl;
    std::cout << request.method()      << std::endl << std::endl;

    http_response response;
    response.status().code()    = 200;
    response.status().message() = "OK";
    response.version( version::http_1_1() );
    response << "Foobar";
    
    std::cout << "Version: " <<  response.version() << std::endl;
    std::cout << "Status: " <<  response.status().code() << " " << response.status().message() << std::endl;
    std::cout << "Body: " <<  response.str() << std::endl;
    
    
    http_request_result result((1));
}
