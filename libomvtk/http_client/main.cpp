#include "http_request.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/concepts.hpp> 
using namespace omvtk::http;

typedef basic_request<void> http_request;

int main(){
    http_request request( "http://www.google.com", method::post );

    request % ContentLength( 0x1000 ) // Da muss ich noch automatisch die größe from stream nehmen :-)
            % Accept( "*/*" )
            % ContentType( "application/llsd+xml" );

    std::cout << request.url()         << std::endl;
    std::cout << request.version()     << std::endl;
    std::cout << request.method()      << std::endl;
}
