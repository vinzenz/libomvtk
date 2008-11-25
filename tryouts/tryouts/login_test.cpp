#include "stdafx.h"

#include <algorithm>
#include <iterator>
#include <map>
#include <iostream>
#include <boost/foreach.hpp>

#include <Poco/Util/Application.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/SharedPtr.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/MD5Engine.h>
#include <Poco/URI.h>
#include "llsd/llsd.h"

struct App : Poco::Util::Application
{
	App(int argc, _TCHAR * argv[])
		: Poco::Util::Application(argc, argv){}
};

template<typename T>
struct wrap
{
	T & _val;
	wrap(T & val): _val(val){ }
	typedef typename T::Iterator iterator;		
	typedef typename T::ConstIterator const_iterator;
	iterator begin(){ return _val.begin(); }
	const_iterator begin() const { return _val.begin(); }
	iterator end(){ return _val.end(); }
	const_iterator end() const { return _val.end(); }
};

template<typename T>
wrap<T> wrapit(T & t)
{
	return wrap<T>(t);
}


#if 0
// Create the CAPS login structure
LLSDMap loginLLSD = new LLSDMap();
loginLLSD["first"] = LLSD.FromString(loginParams.FirstName);
loginLLSD["last"] = LLSD.FromString(loginParams.LastName);
loginLLSD["passwd"] = LLSD.FromString(loginParams.Password);
loginLLSD["start"] = LLSD.FromString(loginParams.Start);
loginLLSD["channel"] = LLSD.FromString(loginParams.Channel);
loginLLSD["version"] = LLSD.FromString(loginParams.Version);
loginLLSD["platform"] = LLSD.FromString(loginParams.Platform);
loginLLSD["mac"] = LLSD.FromString(loginParams.MAC);
loginLLSD["agree_to_tos"] = LLSD.FromBoolean(true);
loginLLSD["read_critical"] = LLSD.FromBoolean(true);
loginLLSD["viewer_digest"] = LLSD.FromString(loginParams.ViewerDigest);
loginLLSD["id0"] = LLSD.FromString(loginParams.id0);
#endif

LLSD::MapPtr MakeLogin(std::string const & first, std::string const & last, std::string const & password)
{
	using namespace LLSD;
	Poco::MD5Engine md5;
	md5.update(password);	
	MapPtr map = Value().ToMap();
	map->insert("first", StringPtr(new String(first)));
	map->insert("last", StringPtr(new String(last)));
	map->insert("passwd", StringPtr(new String("$1$" + md5.digestToHex(md5.digest()))));
	map->insert("start", StringPtr(new String("last")));
	map->insert("channel", StringPtr(new String("contact@virtuosic-bytes.com")));
	map->insert("version", StringPtr(new String("0.0.1")));
	map->insert("platform", StringPtr(new String("Win")));
	map->insert("mac", StringPtr(new String("00:13:8F:63:2B:B5")));
	map->insert("agree_to_tos", BooleanPtr(new Boolean(true)));
	map->insert("read_critical", BooleanPtr(new Boolean(true)));
	map->insert("viewer_digest", StringPtr(new String("")));
	map->insert("id0", (*map)["mac"]);
	map->insert("options", Value().ToArray());
	return map;
}



int _tmain(int argc, _TCHAR* argv[])
{
	using namespace Poco;
	using namespace Poco::Net;

	App application(argc, argv);

	SharedPtr<PrivateKeyPassphraseHandler> ptrAllAccept = SSLManager::instance().clientPassPhraseHandler();
	SharedPtr<InvalidCertificateHandler> ptrInvalidCert = new AcceptCertificateHandler(false);
	SharedPtr<Context> ptrContext = new Context(); 	

	SSLManager::instance().initializeClient(ptrAllAccept, ptrInvalidCert, ptrContext);

	URI uri("https://login.agni.lindenlab.com");
	SharedPtr<HTTPClientSession> session;
	if(uri.getScheme() == "https")
		session = new HTTPSClientSession(uri.getHost(), uri.getPort());
	else
		session = new HTTPClientSession(uri.getHost(), uri.getPort());

	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, "/cgi-bin/login.cgi", Poco::Net::HTTPRequest::HTTP_1_1);	
	std::string loginXml = LLSD::BuildXml(MakeLogin("FirstName","LastName","Password"));
	std::cout << loginXml << std::endl;	
	request.setContentType("application/xml+llsd");
	request.setContentLength(int(loginXml.size())+4);
	session->sendRequest(request) << loginXml << "\r\n\r\n";

	HTTPResponse response;

	std::istream & responseStream = session->receiveResponse(response);
	BOOST_FOREACH(HTTPResponse::HeaderMap::value_type const & val, wrapit(response) )
	{
		std::cout << val.first << ":\t" << val.second << std::endl;
	}
	std::cout << "Reply data: " << std::endl;
	responseStream >> std::noskipws;
	std::string replyStr((std::istream_iterator<char>(responseStream)), (std::istream_iterator<char>()));

	std::cout << replyStr << std::endl;
	LLSD::ValuePtr val = LLSD::ParseXml(replyStr);
	std::cout << "Parsing success: " << std::boolalpha << bool(val) << std::endl;
	
}