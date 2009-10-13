#include <iostream>
#include "http_client.h"
#include "../libomvtk/gridclient.h"
#include "../libomvtk/logger/logger.h"
#include "../libomvtk/llsd/value.h"
#include "../libomvtk/utils/md5.h"
#include "login_xmlrpc.h"

using namespace omvtk;

String build_login_request(String const & firstname, String const & lastname, String const & password)
{
	LLSDValue::Map map;	
	map["first"] 			= firstname;
	map["last"] 			= lastname;
    map["passwd"] 			= "$1$" + MD5::hash(password).to_string();
	map["start"] 			= "last";
	map["channel"] 			= "contact@virtuosic-bytes.com";
	map["version"] 			= "1.23.4.123908";
	map["major"] 			= "1";
	map["minor"] 			= "23";
	map["patch"] 			= "4";
	map["build"] 			= "123908";
	map["platform"] 		= "Win";
	map["mac"] 				= "00:13:8F:63:2B:B5";
	map["agree_to_tos"] 	= true;
	map["read_critical"] 	= true;
	map["viewer_digest"] 	= "68920a26-9f41-b742-a5e6-db6a713dcd96";
	map["id0"] 				= map["mac"];
    LLSDValue::Array arr;
    arr.push_back("login-flags");
    arr.push_back("adult_compliant");
    arr.push_back("event_notifications");
    arr.push_back("ui-config");
    map["options"]          = arr;
    
    // return LoginRequestXMLRPC()(map);

	return "<?xml version=\"1.0\"?>"
           "<llsd>" + LLSDValue(map).xml_encode() + "</llsd>";
        
}
int main(int argc, char const ** argv)
{
    if( argc != 4 ) {
        std::cerr << "http_test_client first last password" << std::endl;
        return EXIT_FAILURE;
    }

    omvtk::logger::set_log_level(omvtk::logger::debug);
    omvtk::GridClient grid;
    omvtk::HttpClient client(grid.network());   
    grid.library().context().set_options(boost::asio::ssl::context::default_workarounds);
	grid.library().context().set_verify_mode(boost::asio::ssl::context::verify_none);
	grid.library().context().load_verify_file("../data/ca.pem");
 
    
    HTTPRequest::HeaderCollection headers;
    String request = build_login_request(argv[1], argv[2], argv[3]);
    headers.insert( std::make_pair("Content-Length", boost::lexical_cast<String>( request.size() ) ) );
    // headers.insert( std::make_pair("Content-Type", "text/xml" ) );
    headers.insert( std::make_pair("Content-Type", "application/xml+llsd" ) );
    headers.insert( std::make_pair("Connection", "Keep-Alive" ) );
    client.post( LLURI(grid.settings().login_uri), request, HttpClient::ProgressHandler(), headers);
    // client.get(omvtk::LLURI("http://www.google.cz"), omvtk::HttpClient::ProgressHandler());
    grid.network().service().run();

    return EXIT_SUCCESS;
}