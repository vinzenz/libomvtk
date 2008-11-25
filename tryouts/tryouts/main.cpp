#include "stdafx.h"
#if 0
#include "llsd\llsd.h"
#include "throw.h"

std::string LLSDNOTATION_TESTSTR =
"["
"{'destination':'http://secondlife.com'}, "
"{'version':i1}, "
"{"
"	'agent_id':u3c115e51-04f4-523c-9fa6-98aff1034730, "
"		'session_id':u2c585cec-038c-40b0-b42e-a25ebab4d132, "
"		'circuit_code':i1075, "
"		'first_name':'Phoenix', "
"		'last_name':'Linden',"
"		'position':[r70.9247,r254.378,r38.7304],"
"		'look_at':[r-0.043753,r-0.999042,r0], "
"		'granters':[ua2e76fcd-9360-4f6d-a924-000000000003],"
"		'attachment_data':"
"	["
"	{"
"		'attachment_point':i2,"
"		'item_id':ud6852c11-a74e-309a-0462-50533f1ef9b3,"
"		'asset_id':uc69b29b1-8944-58ae-a7c5-2ca7b23e22fb"
"	},"
"	{"
"		'attachment_point':i10, "
"			'item_id':uff852c22-a74e-309a-0462-50533f1ef900,"
"			'asset_id':u5868dd20-c25a-47bd-8b4c-dedc99ef9479"
"	}"
"	]"
"}"
"]";

std::string LLSDNOTATION_TESTSTR2 = 
"["
"{"
"	'creation-date':d\"2007-03-15T18:30:18Z\", "
"	'creator-id':u3c115e51-04f4-523c-9fa6-98aff1034730"
"},"
"s(10)\"0123456789\","
"\"Where's the beef?\","
"'Over here.',  "
"b(160)\"default\n"
"{\n"
"    state_entry()\n"
"    {\n"
"        llSay(0, \"Hello, Avatar!\");\n"
"    }\n"
"\n"
"    touch_start(integer total_number)\n"
"    {\n"
"        llSay(0, \"Touched.\");\n"
"    }\n"
"}\n\","
"       b64\"AABAAAAAAAAAAAIAAAA//wAAP/8AAADgAAAA5wAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"       AABkAAAAZAAAAAAAAAAAAAAAZAAAAAAAAAABAAAAAAAAAAAAAAAAAAAABQAAAAEAAAAQAAAAAAAA\r\n"
"		AAUAAAAFAAAAABAAAAAAAAAAPgAAAAQAAAAFAGNbXgAAAABgSGVsbG8sIEF2YXRhciEAZgAAAABc\n"
"		XgAAAAhwEQjRABeVAAAABQBjW14AAAAAYFRvdWNoZWQuAGYAAAAAXF4AAAAIcBEI0QAXAZUAAEAA\n"
"		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\""
"]";

int main()
{
	std::cout << "1st Test..." << std::endl;
	LLSD::ValuePtr result = LLSD::ParseNotation(LLSDNOTATION_TESTSTR);
	std::string strRes = LLSD::BuildNotation(result);
	std::cout << strRes << std::endl;
	std::cout << "\n\nVerification: " << std::boolalpha << (strRes == LLSD::BuildNotation(LLSD::ParseNotation(strRes))) << std::endl;

	std::cout << "\n\n\n2nd Test..." << std::endl;
	result = LLSD::ParseNotation(LLSDNOTATION_TESTSTR2);

	strRes = LLSD::BuildNotation(result);
	std::cout << strRes << std::endl;

	std::cout << "\n\nVerification: " << std::boolalpha << (strRes == LLSD::BuildNotation(LLSD::ParseNotation(strRes))) << std::endl;
	std::cout << "\n\n\n" << std::endl;

	std::cout << "Binary Test: " << std::endl;
	std::vector<boost::uint8_t> binRes = LLSD::BuildBinary(result);
	std::cout << "\n\nVerification: " << std::boolalpha <<  (binRes == LLSD::BuildBinary(LLSD::ParseBinary(binRes))) << std::endl;
	std::cout << LLSD::BuildXml(LLSD::ParseBinary(binRes)) << std::endl;
	return 0;
}


std::string booleanStr = 
"<llsd>"
"<array>"
"<!-- true -->"
"<boolean>1</boolean>"
"<boolean>true</boolean>"
""
"<!-- false -->"
"<boolean>0</boolean>"
"<boolean>false</boolean>"
"<boolean />"
"</array>"
"</llsd>";

std::string LLSDXMLTESTSTRING = "<llsd>"
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

std::string ParseBuildResult = "<llsd>"
"<map>"
"<key>region_id</key>"
"<uuid>67153d5b-3659-afb4-8510-adda2c034649</uuid>"
"<key>scale</key><string>one minute</string>"
"<key>simulator statistics</key>"
"<map>"
"<key>active script count</key><real>4</real>"
"<key>active task count</key><real>0</real>"
"<key>agent ms</key><real>0.0159903</real>"
"<key>agent updates per second</key><real>nan</real>"
"<key>child agent count</key><real>0</real>"
"<key>frame ms</key><real>0.775789</real>"
"<key>image ms</key><real>0.0186596</real>"
"<key>inbound packets per second</key><real>1.22828</real>"
"<key>lsl instructions per second</key><real>0</real>"
"<key>main agent count</key><real>0</real>"
"<key>net ms</key><real>0.315292</real>"
"<key>outbound packets per second</key><real>1.27751</real>"
"<key>pending downloads</key><real>0</real>"
"<key>pending uploads</key><real>0.000109652</real>"
"<key>pysics fps</key><real>44.3891</real>"
"<key>script ms</key><real>0.133884</real>"
"<key>sim fps</key><real>44.389</real>"
"<key>sim other ms</key><real>0.182694</real>"
"<key>sim physics ms</key><real>0.0432306</real>"
"<key>time dilation</key><real>0.987862</real>"
"<key>total task count</key><real>4</real>"
"</map>"
"</map>"
"</llsd>";

int main()
{

	try
	{
		LLSD::ValuePtr val = LLSD::ParseXml(LLSDXMLTESTSTRING);
		std::cout << "Got result: " << std::boolalpha << (val);
		if(val)
		{
			std::cout << " Result is array: " << (val->GetType() == LLSD::VTID_ARRAY) << std::endl;

			std::cout << "Recreating: " << std::endl;
			std::string result = LLSD::BuildXml(val);
			std::cout << result << std::endl;
			std::cout << "Equal size:" << std::boolalpha << (LLSDXMLTESTSTRING.size() == result.size()) << std::endl;
			std::cout << "Input size: "  << LLSDXMLTESTSTRING.size() << " <=> Output size: " << result.size() << std::endl;
			std::cout << "Parse Rebuild equals check " << std::boolalpha << (LLSD::BuildXml(LLSD::ParseXml(result)) == result) << std::endl;
		}
		else
		{
			std::cout << "\n";
		}
	}
	catch (LIBVWException const & e)
	{
		std::cout << "Caught exception: " << e.what() << " Thrown at: " << e.location().file() << ":" << e.location().line() << std::endl;
	}
	catch(std::exception const & e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Caught exception" << std::endl;
	}
}
#endif