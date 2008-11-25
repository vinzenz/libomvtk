#include "../test_suite.h"
#include <Poco/ByteOrder.h>
#include "../../libvw/types/lldate.h"

namespace tut
{
	using vw::LLDate;
	using vw::String;
	struct lldate_data{};

	DEFINE_TEST_GROUP(lldate_data, "vw::LLDate test");

	DEF_TEST(1)
	{
		set_test_name("default initialization test");
		LLDate date;
		ensure(date.get() == LLDate::value_type(Poco::Timestamp(0)));
	}

	DEF_TEST(2)
	{
		set_test_name("serialization to std::ostream and back via std::istream with default initialization");
		std::ostringstream output;
		output << LLDate();
		ensure_not(output.bad());
		std::istringstream input(output.str());
		LLDate readDate;
		input >> readDate;
		ensure_not(input.bad());
		ensure_equals(readDate, LLDate());
	}

	DEF_TEST(3)
	{
		set_test_name("Fractional seconds parser and ensuring that it will be restored");
		// An input which must be parsable although fractions are optional
		std::istringstream input("2006-02-01T14:29:53.43Z0123456789");
		LLDate readDate;
		input >> readDate;

		std::streamsize pos1 = input.tellg();
		input.seekg(0, std::ios_base::end);
		std::streamsize pos2 = input.tellg();
		input.seekg(pos1, std::ios::beg);
		std::ostringstream output;

		output << readDate;
		ensure_not(input.bad());
		ensure_equals(pos2 - pos1, 10);
		ensure_equals(output.str(), "2006-02-01T14:29:53.43Z");
		String rest;
		input >> rest;
		ensure_equals(rest,"0123456789");
	}

	DEF_TEST(4)
	{
		set_test_name("Binary parsing test");
		double r = vw::Real64ByteOrder::convert(&Poco::ByteOrder::toNetwork, 1.);
		vw::Byte * p = reinterpret_cast<vw::Byte*>(&r);
		vw::byte_sub_range br(p,p+8);
		LLDate date(br);
		ensure_equals(date.to_string(), "1970-01-01T00:00:01Z");
	}

	DEF_TEST(5)
	{
		set_test_name("Real64 initialization test");
		double r = 1.;
		LLDate date(r);
		ensure_equals(date.to_string(), "1970-01-01T00:00:01Z");
	}

	DEF_TEST(6)
	{
		set_test_name("UInt32 initialization test");		
		vw::Int32 u = 1;
		LLDate date(u);
		ensure_equals(date.to_string(), "1970-01-01T00:00:01Z");
	}

	DEF_TEST(7)
	{
		set_test_name("LLDate copy test");	
		LLDate date("2006-02-01T14:29:53.43Z");
		LLDate other = date;
		ensure_equals(other.to_string(),"2006-02-01T14:29:53.43Z");
	}

	DEF_TEST(8)
	{
		set_test_name("LLDate compare test");	
		LLDate date("2006-02-01T14:29:53.43Z");
		LLDate other; // Unix Epoch
		ensure(other < date);
		ensure(other <= date);
		ensure(other != date);
		ensure_not(other > date);
		ensure_not(other >= date);
		ensure_not(other == date);

		ensure_not(date < other);
		ensure_not(date <= other);
		ensure_not(date == other);
		ensure(date != other);
		ensure(date > other);
		ensure(date >= other);
	}


	DEF_TEST(9)
	{
		set_test_name("LLDate self assignment test");
		LLDate date;
		date = date;
	}
}

