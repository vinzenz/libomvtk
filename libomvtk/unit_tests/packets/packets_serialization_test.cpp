#include "../test_suite.h"
#include "../../libvw/packets/packets.h"

namespace tut
{
	struct packets_serialization_data{};

	DEFINE_TEST_GROUP(packets_serialization_data, "Packet serialization test");

	DEF_TEST(1)
	{
		using namespace vw::packets;
		TestMessageMessage msg;
		vw::ByteBuffer buffer;
		Serializer serializer(buffer);

		msg.TestBlock1.Test1	   = 1234;
		msg.NeighborBlock[0].Test0 = 1234;
		msg.NeighborBlock[1].Test0 = 1234;
		msg.NeighborBlock[2].Test0 = 1234;

		serialize(serializer, msg);
		
		Deserializer deserializer(buffer);

		TestMessageMessage msg2;

		deserialize(deserializer, msg2);

		vw::ByteBuffer buffer2;
		Serializer serializer2(buffer2);

		serialize(serializer2, msg2);

		ensure(buffer == buffer2);
	}

	DEF_TEST(2)
	{
		using namespace vw::packets;
		set_test_name("Zero encoding test");
		vw::ByteBuffer buf(1023,0);
		buf.front() = MSG_ZEROCODED;
		zero_encode(buf);
		ensure(buf.size() == 14);
		vw::Byte expected_result[] = {MSG_ZEROCODED, 0, 0, 0, 0, 0, 0, 0xff, 0, 0xff, 0, 0xff, 0, 0xf8 };
		ensure(sizeof(expected_result) == 14);
		vw::ByteBuffer buf2(expected_result,expected_result+14);
		ensure_equals(buf,buf2);
	}

	DEF_TEST(3)
	{
		using namespace vw::packets;
		set_test_name("Zero decoding test");
		vw::Byte encoded[] = {MSG_ZEROCODED, 0, 0, 0, 0, 0, 0, 0xff, 0, 0xff, 0, 0xff, 0, 0xf8 };
		ensure(sizeof(encoded) == 14);
		vw::ByteBuffer buf(encoded,encoded+14);		
		vw::ByteBuffer buf2(1023,0);
		buf2.front() = MSG_ZEROCODED;
		zero_decode(buf);
		ensure_equals(buf,buf2);
	}

	DEF_TEST(4)
	{
		using namespace vw::packets;
		set_test_name("Zero encoding with ack test");
		vw::ByteBuffer buf(1023+5,0);
		buf.back() = 1;
		buf.front() = MSG_APPENDED_ACKS|MSG_ZEROCODED;
		zero_encode(buf);
		ensure(buf.size() == 19);
		vw::Byte expected_result[] = {MSG_APPENDED_ACKS|MSG_ZEROCODED, 0, 0, 0, 0, 0, 0, 0xff, 0, 0xff, 0, 0xff, 0, 0xf8, 0, 0, 0, 0, 1};
		ensure(sizeof(expected_result) == 19);
		vw::ByteBuffer buf2(expected_result,expected_result+19);
		ensure_equals(buf,buf2);
	}
}

