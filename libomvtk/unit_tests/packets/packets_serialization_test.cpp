#include "../test_suite.h"
#include "../../libomvtk/packets/packets.h"

namespace tut
{
	struct packets_serialization_data{};

	DEFINE_TEST_GROUP(packets_serialization_data, "Packet serialization test");

	DEF_TEST(1)
	{
		using namespace omvtk::packets;
		TestMessageMessage msg;
		omvtk::ByteBuffer buffer;
		Serializer serializer(buffer);

		msg.TestBlock1.Test1	   = 1234;
		msg.NeighborBlock[0].Test0 = 1234;
		msg.NeighborBlock[1].Test0 = 1234;
		msg.NeighborBlock[2].Test0 = 1234;

		serialize(serializer, msg);
		
		Deserializer deserializer(buffer);

		TestMessageMessage msg2;

		deserialize(deserializer, msg2);

		omvtk::ByteBuffer buffer2;
		Serializer serializer2(buffer2);

		serialize(serializer2, msg2);

		ensure(buffer == buffer2);
	}

	DEF_TEST(2)
	{
		using namespace omvtk::packets;
		set_test_name("Zero encoding test");
		omvtk::ByteBuffer buf(1023,0);
		buf.front() = MSG_ZEROCODED;
		zero_encode(buf);
		ensure(buf.size() == 14);
		omvtk::Byte expected_result[] = {MSG_ZEROCODED, 0, 0, 0, 0, 0, 0, 0xff, 0, 0xff, 0, 0xff, 0, 0xf8 };
		ensure(sizeof(expected_result) == 14);
		omvtk::ByteBuffer buf2(expected_result,expected_result+14);
		ensure_equals(buf,buf2);
	}

	DEF_TEST(3)
	{
		using namespace omvtk::packets;
		set_test_name("Zero decoding test");
		omvtk::Byte encoded[] = {MSG_ZEROCODED, 0, 0, 0, 0, 0, 0, 0xff, 0, 0xff, 0, 0xff, 0, 0xf8 };
		ensure(sizeof(encoded) == 14);
		omvtk::ByteBuffer buf(encoded,encoded+14);		
		omvtk::ByteBuffer buf2(1023,0);
		buf2.front() = MSG_ZEROCODED;
		zero_decode(buf);
		ensure_equals(buf,buf2);
	}

	DEF_TEST(4)
	{
		using namespace omvtk::packets;
		set_test_name("Zero encoding with ack test");
		omvtk::ByteBuffer buf(1023+5,0);
		buf.back() = 1;
		buf.front() = MSG_APPENDED_ACKS|MSG_ZEROCODED;
		zero_encode(buf);
		ensure(buf.size() == 19);
		omvtk::Byte expected_result[] = {MSG_APPENDED_ACKS|MSG_ZEROCODED, 0, 0, 0, 0, 0, 0, 0xff, 0, 0xff, 0, 0xff, 0, 0xf8, 0, 0, 0, 0, 1};
		ensure(sizeof(expected_result) == 19);
		omvtk::ByteBuffer buf2(expected_result,expected_result+19);
		ensure_equals(buf,buf2);
	}
}

