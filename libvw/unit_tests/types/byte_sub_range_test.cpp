#include "../test_suite.h"
#include "../../libvw/types/sub_range.h"
#include <list>

namespace tut
{
	using vw::byte_sub_range;
	using vw::Byte;
	struct byte_sub_range_data{};

	DEFINE_TEST_GROUP(byte_sub_range_data, "vw::byte_sub_range test");

	DEF_TEST(1)
	{		
		set_test_name("byte_sub_range pointer accept check");
		ensure("type check must take char*",		byte_sub_range::iterator_check<char*>::value	   );		
		ensure("type check must take char const*",	byte_sub_range::iterator_check<char const*>::value );		
		ensure("type check must take Byte*",		byte_sub_range::iterator_check<Byte*>::value	   );		
		ensure("type check must take Byte const*",	byte_sub_range::iterator_check<Byte const*>::value );		
	}

	DEF_TEST(2)
	{
		set_test_name("byte_sub_range vector<char> iterators accept check");
		ensure("type check must take vector<char>::iterator",	byte_sub_range::iterator_check<std::vector<char>::iterator>::value );		
		ensure("type check must take vector<char>::const_iterator",	byte_sub_range::iterator_check<std::vector<char>::const_iterator>::value );		
		ensure_not("type check must not take vector<char>::reverse_iterator",	byte_sub_range::iterator_check<std::vector<char>::reverse_iterator>::value );		
		ensure_not("type check must not take vector<char>::const_reverse_iterator",	byte_sub_range::iterator_check<std::vector<char>::const_reverse_iterator>::value );		
	}

	DEF_TEST(3)
	{
		// This test represents invalid iterators
		set_test_name("byte_sub_range list<char> iterator refusal check");
		ensure_not("type check must not take list<char>::iterator",	byte_sub_range::iterator_check<std::list<char>::iterator>::value );		
		ensure_not("type check must not take list<char>::const_iterator",	byte_sub_range::iterator_check<std::list<char>::const_iterator>::value );		
		ensure_not("type check must not take list<char>::reverse_iterator",	byte_sub_range::iterator_check<std::list<char>::reverse_iterator>::value );		
		ensure_not("type check must not take list<char>::const_reverse_iterator",	byte_sub_range::iterator_check<std::list<char>::const_reverse_iterator>::value );		
	}

	DEF_TEST(4)
	{
		set_test_name("byte_sub_range sizeof(T) != sizeof(Byte) T* refusal check");
		ensure_not("type check must not take vw::UInt16*",	byte_sub_range::iterator_check<vw::UInt16*>::value );		
		ensure_not("type check must not take vw::UInt32*",	byte_sub_range::iterator_check<vw::UInt32*>::value );		
		ensure_not("type check must not take vw::UInt64*",	byte_sub_range::iterator_check<vw::UInt64*>::value );		
	}

	DEF_TEST(5)
	{
		set_test_name("byte_sub_range vw::String iterator accept check");
		ensure("type check must take vw::String::iterator",	byte_sub_range::iterator_check<vw::String::iterator>::value );		
		ensure("type check must take vw::String::const_iterator",	byte_sub_range::iterator_check<vw::String::const_iterator>::value );		
		ensure_not("type check must not take vw::String::reverse_iterator",	byte_sub_range::iterator_check<vw::String::reverse_iterator>::value );		
		ensure_not("type check must not take vw::String::const_reverse_iterator",	byte_sub_range::iterator_check<vw::String::const_reverse_iterator>::value );		
	}

	DEF_TEST(6)
	{
		set_test_name("runtime checks string to sr and from sr to string or vector");
		vw::String test_value("abcdefghijklmopqrstuvwxyz");
		byte_sub_range sr(test_value.begin(), test_value.end());
		ensure_equals("sr.size() must be equal to test_value.size()", size_t(sr.size()), test_value.size());
		ensure_equals("string constructed from sr must be equal to test_value string", vw::String(sr.begin(), sr.end()), test_value);
		std::vector<char> test_vector(test_value.begin(), test_value.end());
		ensure("vector constructed from sr must be equal to vector constructed from test_value string", std::vector<char>(sr.begin(), sr.end()) == test_vector);
	}

	DEF_TEST(7)
	{
		set_test_name("runtime checks char const * buffer to sr and compared to vector<Byte> constructed from it");
		char const * buffer = "abcdefghijklmnopqrstuvwxyz";
		size_t const buffer_len = strlen(buffer);
		byte_sub_range sr(buffer, buffer + buffer_len);
		ensure("sr must be equal to vector<byte> initialized with the buffer", std::vector<Byte>(sr.begin(), sr.end()) == std::vector<Byte>(buffer, buffer + buffer_len));
	}

	DEF_TEST(8)
	{
		vw::String empty_string;
		set_test_name("empty subrange checks");
		ensure("empty subrange size must be 0", byte_sub_range().size() == 0);
		ensure("empty subrange size must be 0", byte_sub_range(empty_string.begin(), empty_string.end()).size() == 0);
	}
}
