#include "../test_suite.h"
#include "../../libomvtk/llsd/notation.h"

omvtk::String NOTATION_PARSER_TEST_STRING1 = 
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

omvtk::String NOTATION_PARSER_TEST_STRING2 = 
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
"       AABkAAAAZAAAAAAAAAAAAAAAZAAAAAAAAAABAAAAAAAAAAAAAAAAAAAABQAAAAEAAAAQAAAAAAAA\n"
"		AAUAAAAFAAAAABAAAAAAAAAAPgAAAAQAAAAFAGNbXgAAAABgSGVsbG8sIEF2YXRhciEAZgAAAABc\n"
"		XgAAAAhwEQjRABeVAAAABQBjW14AAAAAYFRvdWNoZWQuAGYAAAAAXF4AAAAIcBEI0QAXAZUAAEAA\n"
"		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\""
"]";

namespace tut
{
	struct llsd_notation_parser_data{};

	DEFINE_TEST_GROUP(llsd_notation_parser_data, "LLSD Notation parser test");

	DEF_TEST(1)
	{
		try
		{
			omvtk::LLSDValue value = omvtk::detail::Notation::Parser::Parse(NOTATION_PARSER_TEST_STRING1.begin(),NOTATION_PARSER_TEST_STRING1.end());
			omvtk::String encoded = value.notation_encode();
			ensure_equals(omvtk::detail::Notation::Parser::Parse(encoded.begin(), encoded.end()).notation_encode(),encoded);
        	}
        	catch(Poco::Exception const & e)
	        {
        	    std::cout << e.displayText() << std::endl;
	            throw;
        	}
	}

	DEF_TEST(2)
	{
		try
	        {
		    omvtk::LLSDValue value = omvtk::detail::Notation::Parser::Parse(NOTATION_PARSER_TEST_STRING2.begin(),NOTATION_PARSER_TEST_STRING2.end());
		    omvtk::String encoded = value.notation_encode();
		    ensure_equals(omvtk::detail::Notation::Parser::Parse(encoded.begin(), encoded.end()).notation_encode(),encoded);
        	}
	        catch(Poco::Exception const & e)
        	{
	            std::cout << e.displayText() << std::endl;
        	    throw;
	        }
	}
}
