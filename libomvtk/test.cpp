#include "network/https_client.h"
#include "logger/logger.h"
#include <typeinfo>
#include <boost/lexical_cast.hpp>
#include "llsd/value.h"
#include <Poco/MD5Engine.h>
using namespace omvtk;

void on_received(HTTPResponse const  & res)
{
    std::cout     << "Received response: \n"
                << String(res.content().begin(),res.content().end()) << std::endl;
}

String build_login_request(String const & firstname, String const & lastname, String const & password)
{
    LLSDValue::Map map;
    Poco::MD5Engine md5;
    md5.update(password);    
    map["first"]             = firstname;
    map["last"]             = lastname;
    map["passwd"]             = "$1$" + md5.digestToHex(md5.digest());
    map["start"]             = "last";
    map["channel"]             = "contact@virtuosic-bytes.com";
    map["version"]             = "0.0.1";
    map["platform"]         = "Win";
    map["mac"]                 = "00:13:8F:63:2B:B5";
    map["agree_to_tos"]     = true;
    map["read_critical"]     = true;
    map["viewer_digest"]     = "";
    map["id0"]                 = map["mac"];

    return LLSDValue(map).xml_encode();
}

int main(int argc, char * argv[])
{
    if(argc < 4)
    {
        std::cout << "Usage: " << argv[0] << " first last password" << std::endl;
        return 0;
    }
    try
    {
        logger::init();
        boost::asio::io_service service;
        boost::asio::ssl::context ctx(service, boost::asio::ssl::context::sslv23);
        ctx.set_options(boost::asio::ssl::context::default_workarounds);
        ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
        ctx.load_verify_file("data/ca.pem");    

        {        
            HTTPSClient::Pointer ptr = HTTPSClient::create(ctx, service);    
            HTTPRequest request(LLURI("https://login.agni.lindenlab.com/cgi-bin/login.cgi"),HTTP::METHOD::POST);
            String llsd = "<llsd>" + build_login_request(argv[1],argv[2],argv[3]) + "</llsd>\r\n\r\n";
            request.content().assign(llsd.begin(),llsd.end());

            request.header().content_type()     = "application/xml+llsd";
            request.header().content_length()     = boost::lexical_cast<String>(llsd.size());
            request.header().connection()         = "close";

            std::cout << "Request looks like: " << std::endl;
            std::cout << request.header().request() << llsd;
            std::cout << std::endl;

            if(!ptr->async_request(request, on_received))
            {
                std::cout << "Request setup failed!" << std::endl;
                return 0;
            }
            
            std::cout << "Starting service..." << std::endl;
        }

        service.run();

        std::cout << "Service processed the queue. Request should have finished" << std::endl;
        logger::shutdown();
    }
    catch(std::exception const & e)
    {
        std::cout << "Exception caught: " << e.what() << std::endl << "Exception type: " << typeid(e).name();
    }
    return 0;
}

