#include "../test_suite.h"
#include "../../libomvtk/llsd/value.h"
#include "../../libomvtk/types/byte_order.h"

namespace tut
{
	using omvtk::LLSDValue;
	struct llsdvalue_data{};

	DEFINE_TEST_GROUP(llsdvalue_data, "omvtk::LLSDValue test");

	DEF_TEST(1)
	{
		set_test_name("default initialization test");
		LLSDValue val;
		ensure_not(val);
		ensure_equals(val.type(), LLSDValue::VT_UNDEF);
	}

	DEF_TEST(2)
	{
		set_test_name("copy test");
		LLSDValue val;
		LLSDValue otherVal = val;
		ensure_equals(val.type(),otherVal.type());
	}

	DEF_TEST(3)
	{
		set_test_name("boolean test");
		LLSDValue val = true;
		ensure_equals(val.type(), LLSDValue::VT_BOOLEAN);
		ensure_equals(val.boolean(),true);
		LLSDValue const cval = val;
		ensure_equals(cval.boolean(),true);
		ensure_equals(val.xml_encode(), "<boolean>1</boolean>");
		ensure_equals(val.notation_encode(), "1");
		LLSDValue::Binary serializedBin;
		serializedBin.push_back('1');
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(4)
	{
		set_test_name("integer test");
		LLSDValue val = omvtk::Int32(100);
		ensure_equals(val.type(),LLSDValue::VT_INTEGER);
		ensure_equals(val.integer(), 100);
		LLSDValue const cval = val;
		ensure_equals(val.integer(),100);
		ensure_equals(val.xml_encode(), "<integer>100</integer>");
		ensure_equals(val.notation_encode(), "i100");
		LLSDValue::Binary serializedBin;
		serializedBin.push_back('i');
		omvtk::Int32 integer = omvtk::to_network(val.integer());
		omvtk::Byte * p = reinterpret_cast<omvtk::Byte*>(&integer);
		serializedBin.insert(serializedBin.end(), p, p+sizeof(omvtk::Int32));
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(5)
	{
		set_test_name("real number test");
		LLSDValue val = 123.456789;
		ensure_equals(val.type(), LLSDValue::VT_REAL);
		ensure_equals(val.real(), 123.456789);
		LLSDValue const cval = val;
		ensure_equals(val.real(), 123.456789);
		ensure_equals(val.xml_encode(), "<real>123.456789</real>");
		ensure_equals(val.notation_encode(), "r123.456789");
		LLSDValue::Binary serializedBin;
		serializedBin.push_back('r');
		omvtk::Real64 real = omvtk::to_network( val.real() );
		omvtk::Byte * p = reinterpret_cast<omvtk::Byte*>(&real);
		serializedBin.insert(serializedBin.end(), p, p+sizeof(omvtk::Real64));
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(6)
	{
		set_test_name("string test");
		LLSDValue val = "Hello World!";
		ensure_equals(val.type(), LLSDValue::VT_STRING);
		ensure_equals(val.string(), "Hello World!");
		LLSDValue const cval = val;
		ensure_equals(cval.string(), "Hello World!");
		ensure_equals(val.xml_encode(), "<string>Hello World!</string>");
		ensure_equals(val.notation_encode(), "'Hello World!'");
		char const * p = "s\0\0\0\x0cHello World!";
		LLSDValue::Binary serializedBin(p,p+17);		
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(7)
	{
		set_test_name("uri test");
		LLSDValue val = omvtk::LLURI("http://www.google.com");
		ensure_equals(val.type(), LLSDValue::VT_URI);
		ensure_equals(val.uri().to_string(), "http://www.google.com");
		LLSDValue const cval = val;
		ensure_equals(val.uri().to_string(), "http://www.google.com");
		ensure_equals(val.xml_encode(), "<url>" + val.uri().to_string() + "</url>");
		ensure_equals(val.notation_encode(), "l\"" + val.uri().to_string() + "\"");
		char const * p = "l\0\0\0\x15http://www.google.com";
		LLSDValue::Binary serializedBin(p,p+26);		
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(8)
	{
		set_test_name("uuid test");
		LLSDValue val = omvtk::LLUUID();
		ensure_equals(val.type(), LLSDValue::VT_UUID);
		ensure_equals(val.uuid(), omvtk::LLUUID::Zero);
		LLSDValue const cval = val;
		ensure_equals(cval.uuid(), omvtk::LLUUID::Zero);
		ensure_equals(val.xml_encode(),"<uuid>" + omvtk::LLUUID::Zero.to_string() + "</uuid>");
		ensure_equals(val.notation_encode(),"u" + omvtk::LLUUID::Zero.to_string());
		LLSDValue::Binary serializedBin(17,0);
		serializedBin[0] = 'u';
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(9)
	{
		set_test_name("date test");
		omvtk::LLDate date("2008-07-25T18:20:00Z");
		LLSDValue val = date;
		ensure_equals(val.type(), LLSDValue::VT_DATE);
		ensure_equals(val.date(), date);
		LLSDValue const cval = val;
		ensure_equals(cval.date(), date);
		ensure_equals(val.xml_encode(), "<date>2008-07-25T18:20:00Z</date>");
		ensure_equals(val.notation_encode(), "d\"2008-07-25T18:20:00Z\"");
		LLSDValue::Binary serializedBin;
		serializedBin.push_back('d');
		omvtk::Real64 secs = omvtk::to_network( val.date().to_real() );
		omvtk::Byte * p = reinterpret_cast<omvtk::Byte*>(&secs);
		serializedBin.insert(serializedBin.end(), p, p+sizeof(omvtk::Real64));
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(10)
	{
		set_test_name("binary test");
		static omvtk::Byte const test_data[] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
		LLSDValue::Binary bin(test_data,test_data+sizeof(test_data));
		LLSDValue val = bin;
		ensure_equals(val.type(), LLSDValue::VT_BINARY);
		ensure_equals(val.binary(), bin);
		LLSDValue const cval = val;
		ensure_equals(cval.binary(), bin);
		ensure_equals(val.xml_encode(),"<binary encoding=\"base64\">AQIDBAUGBwgJ</binary>");
		ensure_equals(val.notation_encode(),"b64\"AQIDBAUGBwgJ\"");
		char const * p = "b\0\0\0\x09";
		LLSDValue::Binary serializedBin(p,p+5);
		serializedBin.insert(serializedBin.end(), test_data, test_data+sizeof(test_data));
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(11)
	{
		set_test_name("map test");
		LLSDValue::Map map;
		map["test"] = LLSDValue("Test");
		LLSDValue val = map;
		ensure_equals(val.type(), LLSDValue::VT_MAP);
		ensure(val.map() == map);
		LLSDValue const cval = val;
		ensure(cval.map() == map);
		ensure_equals(val.xml_encode(),"<map><key>test</key><string>Test</string></map>");
		ensure_equals(val.notation_encode(),"{'test':'Test'}");
		char const * p = "{\0\0\0\1s\0\0\0\4tests\0\0\0\4Test}";
		LLSDValue::Binary serializedBin(p,p+24);
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}

	DEF_TEST(12)
	{
		set_test_name("array test");
		LLSDValue::Array arr;
		arr.push_back(LLSDValue("test"));
		LLSDValue val = arr;
		ensure_equals(val.type(), LLSDValue::VT_ARRAY);
		ensure(val.array() == arr);
		LLSDValue const cval = val;
		ensure(cval.array() == arr);
		ensure_equals(val.xml_encode(),"<array><string>test</string></array>");
		ensure_equals(val.notation_encode(),"['test']");
		char const * p = "[\0\0\0\1s\0\0\0\4test]";
		LLSDValue::Binary serializedBin(p,p+15);
		LLSDValue::Binary output;
		val.binary_encode(output);
		ensure(output == serializedBin);
	}
}

