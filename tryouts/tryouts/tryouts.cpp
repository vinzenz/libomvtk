#include "stdafx.h"
#if 0
//#include <windows.h>
//#include <curl/curl.h>
//#include <curl/easy.h>
#include <iostream>
#include <boost/foreach.hpp>
#include <string>
#include "llsd/llsd.h"
#include "base64.h"

/**
* Undefined: '!'<br>
* Boolean: 't' for true 'f' for false<br>
* Integer: 'i' + 4 bytes network byte order<br>
* Real: 'r' + 8 bytes IEEE double<br>
* UUID: 'u' + 16 byte unsigned integer<br>
* String: 's' + 4 byte integer size + string<br>
*  strings also secretly support the notation format
* Date: 'd' + 8 byte IEEE double for seconds since epoch<br>
* URI: 'l' + 4 byte integer size + string uri<br>
* Binary: 'b' + 4 byte integer size + binary data<br>
* Array: '[' + 4 byte integer size  + all values + ']'<br>
* Map: '{' + 4 byte integer size  every(key + value) + '}'<br>
*  map keys are serialized as s + 4 byte integer size + string or in the
*  notation format.
*/

// map: { string:object, string:object }
// array: [ object, object, object ]
// undef: !
// boolean: true | false | 1 | 0 | T | F | t | f | TRUE | FALSE
// integer: i####
// real: r####
// uuid: u####
// string: "g'day" | 'have a "nice" day' | s(size)"raw data"
// uri: l"escaped"
// date: d"YYYY-MM-DDTHH:MM:SS.FFZ"
// binary: b##"ff3120ab1" | b(size)"raw data"

std::string LLSDXMLTESTSTRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<llsd>"
"<map>"
"<key>region_id</key>"
"<uuid>67153d5b-3659-afb4-8510-adda2c034649</uuid>"
"<key>scale</key>"
"<string>one minute</string>"
"<key>simulator statistics</key>"
"<map>"
"<key>time dilation</key><real>0.9878624</real>"
"<key>sim fps</key><real>44.38898</real>"
"<key>pysics fps</key><real>44.38906</real>"
"<key>agent updates per second</key><real>nan</real>"
"<key>lsl instructions per second</key><real>0</real>"
"<key>total task count</key><real>4</real>"
"<key>active task count</key><real>0</real>"
"<key>active script count</key><real>4</real>"
"<key>main agent count</key><real>0</real>"
"<key>child agent count</key><real>0</real>"
"<key>inbound packets per second</key><real>1.228283</real>"
"<key>outbound packets per second</key><real>1.277508</real>"
"<key>pending downloads</key><real>0</real>"
"<key>pending uploads</key><real>0.0001096525</real>"
"<key>frame ms</key><real>0.7757886</real>"
"<key>net ms</key><real>0.3152919</real>"
"<key>sim other ms</key><real>0.1826937</real>"
"<key>sim physics ms</key><real>0.04323055</real>"
"<key>agent ms</key><real>0.01599029</real>"
"<key>image ms</key><real>0.01865955</real>"
"<key>script ms</key><real>0.1338836</real>"
"</map>"
"</map>"
"</llsd>";


int writer(char * buffer, size_t chunk, size_t cnt, std::string * buf)
{
	std::string tmp(buffer, buffer + (chunk * cnt));
	*buf += tmp;

	return int(chunk * cnt);
}
#include <algorithm>
#include <iterator>
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
#include <Poco/URI.h>

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


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace Poco;
	using namespace Poco::Net;
	
	App application(argc, argv);
	
	SharedPtr<PrivateKeyPassphraseHandler> ptrAllAccept = SSLManager::instance().clientPassPhraseHandler();
	SharedPtr<InvalidCertificateHandler> ptrInvalidCert = new AcceptCertificateHandler(false);
	SharedPtr<Context> ptrContext = new Context(); 	
	
	SSLManager::instance().initializeClient(ptrAllAccept, ptrInvalidCert, ptrContext);

	URI uri("http://www.google.de");
	SharedPtr<HTTPClientSession> session;
	if(uri.getScheme() == "https")
		session = new HTTPSClientSession(uri.getHost(), uri.getPort());
	else
		session = new HTTPClientSession(uri.getHost(), uri.getPort());

	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.toString(), Poco::Net::HTTPRequest::HTTP_1_1);	
	
	HTMLForm form(HTMLForm::ENCODING_URL);	
	form.prepareSubmit(request);
	//form.write(
		session->sendRequest(request);
	//	);

	HTTPResponse response;
		
	std::istream & responseStream = session->receiveResponse(response);
	BOOST_FOREACH(HTTPResponse::HeaderMap::value_type const & val, wrapit(response) )
	{
		std::cout << val.first << ":\t" << val.second << std::endl;
	}

	std::cout << std::endl;
//	std::cout << "Status: " << response.getStatus() << std::endl;
//	std::cout << "DataLen: " << response.getContentLength() << std::endl;
//	std::cout << "Content-Type: " << response.getContentType() << std::endl;
	
	
	std::cout << responseStream.rdbuf();
		return 0;
//	assert(argc > 1);
	char * args = 0;
	std::string buf;
#if 0
	curl_global_init(CURL_GLOBAL_ALL);

	CURL * pCurl = curl_easy_init();

	CURLcode err = CURLE_OK;
	err = curl_easy_setopt(pCurl, CURLOPT_URL, "https://cap.secondlife.com/get_reg_capabilities");
	err = curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, writer);
	err = curl_easy_setopt(pCurl, CURLOPT_POST, 1);
	err = curl_easy_setopt(pCurl, CURLOPT_POSTFIELDS, args);
	err = curl_easy_setopt(pCurl, CURLOPT_POSTFIELDSIZE, strlen(args ? args : ""));
	err = curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, &buf);
	err = curl_easy_setopt(pCurl, CURLOPT_SSL_VERIFYPEER, false);
	err = curl_easy_perform(pCurl);

	std::cout << curl_easy_strerror(err) << std::endl;
#endif
	std::cout << buf << std::endl;
	std::cout << "\n\n\nParsing...\n";
	LLSD::ValuePtr val = LLSD::ParseXml(LLSDXMLTESTSTRING);
	if(val && val->GetType() == LLSD::VTID_MAP)
	{
		std::cout << "Done parsing" << std::endl;

		LLSD::MapPtr map = val->AsMap(val);
		std::cout << LLSD::BuildXml(map) << std::endl;
	}

	return 0;
}

#endif