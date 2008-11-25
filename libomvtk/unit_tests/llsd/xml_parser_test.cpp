#include "../test_suite.h"
#include "../../libvw/llsd/xml.h"

vw::String XML_PARSER_TEST_STRING1 = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
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

namespace tut
{
	struct llsd_xml_parser_data{};

	DEFINE_TEST_GROUP(llsd_xml_parser_data, "LLSD XML parser test");

	DEF_TEST(1)
	{
		vw::LLSDValue value = vw::detail::XML::Parser::Parse(XML_PARSER_TEST_STRING1.begin(),XML_PARSER_TEST_STRING1.end());
		vw::String encoded = value.xml_encode();
		ensure_equals(vw::detail::XML::Parser::Parse(encoded.begin(), encoded.end()).xml_encode(),encoded);
	}

	DEF_TEST(2)
	{
		vw::String empty;
		vw::LLSDValue value = vw::detail::XML::Parser::Parse(empty.begin(),empty.end());
		vw::String encoded = value.xml_encode();
		ensure_equals(vw::detail::XML::Parser::Parse(encoded.begin(), encoded.end()).xml_encode(),encoded);
	}
}

