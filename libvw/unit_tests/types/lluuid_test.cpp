#include "../test_suite.h"
#include "../../libvw/types/lluuid.h"

namespace tut
{
	using vw::LLUUID;
	using vw::ByteBuffer;
	using vw::String;
	
	struct lluuid_data{};

	DEFINE_TEST_GROUP(lluuid_data,"vw::LLUUID test");

	DEF_TEST(1)
	{
		set_test_name("zero initialization");
		LLUUID uuid;
		ensure("must be zero", uuid.is_zero());
	}

	DEF_TEST(2)
	{
		set_test_name("zero UUID from string");
		LLUUID uuid("00000000-0000-0000-0000-000000000000");
		ensure("must be zero", uuid.is_zero());
	}

	DEF_TEST(3)
	{
		set_test_name("zero UUID from buffer");
		LLUUID uuid(ByteBuffer(16,0));
		ensure("must be zero", uuid.is_zero());
	}

	DEF_TEST(4)
	{
		set_test_name("UUID from and to string check");
		vw::String uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";
		LLUUID uuid(uuid_str);
		ensure("uuid shall not be zero", !uuid.is_zero());
		ensure_equals("uuid strings have to be equal", uuid_str, uuid.to_string());		
	}

	DEF_TEST(5)
	{
		set_test_name("UUID from and to buffer and string check");
		static char const * data = "\xd7\xf4\xae\xca\x88\xf1\x42\xa1\xb3\x85\xb9\xdb\x18\xab\xb2\x55";
		static String uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";
		static String ensure_msg = "to string result must be '" + uuid_str + "'";
		ByteBuffer buf(data, data + 16);
		LLUUID uuid(buf);
		ensure("uuid shall not be zero", !uuid.is_zero());
		ensure("uuid byte buffers have to be equal", buf == uuid.to_binary());		
		ensure_equals(ensure_msg.c_str(), uuid_str, uuid.to_string());
	}

	DEF_TEST(6)
	{
		set_test_name("UUID compare operators check for two equal UUIDs");

		ensure("compare equal", LLUUID::Zero == LLUUID::Zero);
		ensure_not("compare not equal", LLUUID::Zero != LLUUID::Zero);
		ensure_not("compare greater than", LLUUID::Zero > LLUUID::Zero);
		ensure("compare greater than or equal", LLUUID::Zero >= LLUUID::Zero);
		ensure_not("compare less than", LLUUID::Zero < LLUUID::Zero);
		ensure("compare less than or equal", LLUUID::Zero <= LLUUID::Zero);
	}

	DEF_TEST(7)
	{
		set_test_name("UUID compare operators check for two different UUIDs");
		static String const uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";
		LLUUID uuid(uuid_str);

		ensure_not("compare equal", LLUUID::Zero == uuid);
		ensure("compare not equal", LLUUID::Zero != uuid);
		ensure_not("compare greater than", LLUUID::Zero > uuid);
		ensure_not("compare greater than or equal", LLUUID::Zero >= uuid);
		ensure("compare less than", LLUUID::Zero < uuid);
		ensure("compare less than or equal", LLUUID::Zero <= uuid);

		ensure_not("compare equal", uuid == LLUUID::Zero);
		ensure("compare not equal", uuid != LLUUID::Zero);
		ensure("compare greater than", uuid > LLUUID::Zero);
		ensure("compare greater than or equal", uuid >= LLUUID::Zero);
		ensure_not("compare less than", uuid < LLUUID::Zero);
		ensure_not("compare less than or equal", uuid <= LLUUID::Zero);
	}

	DEF_TEST(8)
	{
		set_test_name("UUID copying test");

		static String const uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";

		LLUUID uuid(LLUUID::Zero);
		ensure_equals("have to be equal", LLUUID::Zero, uuid);
		ensure("has to be zero", uuid.is_zero());
		uuid = LLUUID::Zero;
		ensure_equals("have to be equal", LLUUID::Zero, uuid);
		ensure("has to be zero", uuid.is_zero());
		uuid = LLUUID(uuid_str);
		ensure("have not to be equal", LLUUID::Zero != uuid);
		ensure_not("has not to be zero", uuid.is_zero());
	}

	DEF_TEST(9)
	{
		set_test_name("istream test");
		LLUUID uuid;
		ensure("must be zero", uuid.is_zero());
		std::istringstream is("d7f4aeca-88f1-42a1-b385-b9db18abb255");
		is >> uuid;
		ensure("stream must be still in a valid state", is != 0);
		ensure_not("uuid must not be zero", uuid.is_zero());
	}

	DEF_TEST(10)
	{
		set_test_name("ostream test");
		static String const uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";
		LLUUID uuid(uuid_str);
		ensure_not("must not be zero", uuid.is_zero());
		std::ostringstream os;
		os << uuid;
		ensure("stream must be still in a valid state", os != 0);
		ensure_equals("os.str() must equal used string", uuid_str, os.str() );
	}

	DEF_TEST(11)
	{
		set_test_name("self assignment test");
		static String const uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";
		LLUUID uuid(uuid_str);
		uuid = uuid;
		ensure_equals("has to be equal", uuid.to_string(), uuid_str);
	}

	DEF_TEST(12)
	{
		set_test_name("byte_sub_range initialization test");
		static char const * data = "\xd7\xf4\xae\xca\x88\xf1\x42\xa1\xb3\x85\xb9\xdb\x18\xab\xb2\x55";
		static String const uuid_str = "d7f4aeca-88f1-42a1-b385-b9db18abb255";
		vw::byte_sub_range sr(data, data + 16);
		LLUUID uuid(sr);
		uuid = uuid;
		ensure_equals("has to be equal", uuid.to_string(), uuid_str);
	}

}

