#include "http_test_server.h"

int main(int argc, char const ** argv)
{
    try
    {
        if(argc != 2)
        {
            std::cout << "Usage: test_server <PORT>" << std::endl;
            return EXIT_FAILURE;
        }
        
        boost::asio::io_service service;        
        vw::testenv::HTTPTestServer server(service, atoi(argv[1]));
        
        service.run();
    }
    catch(...)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
