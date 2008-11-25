#include "../test_suite.h"
#include "../../libomvtk/types/lluri.h"

namespace tut
{
	using omvtk::LLURI;
	using omvtk::String;
	struct lluri_data{};

	DEFINE_TEST_GROUP(lluri_data, "omvtk::LLURI test");

	DEF_TEST(1)
	{
		set_test_name("default initialization test");
		LLURI uri;
		ensure("must be empty", uri.to_string().empty());
	}

	DEF_TEST(2)
	{
		static String const test_uri = "http://www.google.com";
		set_test_name("test uri: " + test_uri);
		LLURI uri(test_uri);
		ensure_equals("Port must be 80", uri.get().getPort(), 80);
		ensure_equals("Host must be www.google.com", uri.get().getHost(), "www.google.com");
		ensure_equals("Scheme must be http", uri.get().getScheme(), "http");
	}

	DEF_TEST(3)
	{
		static String const test_uri = "https://www.google.com";
		set_test_name("test uri: " + test_uri);
		LLURI uri(test_uri);
		ensure_equals("Port must be 443", uri.get().getPort(), 443);
		ensure_equals("Host must be www.google.com", uri.get().getHost(), "www.google.com");
		ensure_equals("Scheme must be http", uri.get().getScheme(), "https");
	}

	DEF_TEST(4)
	{
		static String const test_uri = "https://www.google.com:8443";
		set_test_name("test uri: " + test_uri);
		LLURI uri(test_uri);
		ensure_equals("Port must be 443", uri.get().getPort(), 8443);
		ensure_equals("Host must be www.google.com", uri.get().getHost(), "www.google.com");
		ensure_equals("Scheme must be http", uri.get().getScheme(), "https");
	}

	DEF_TEST(5)
	{
		static String const test_uri = "https://www.google.com:8443/caps/login.cgi";
		set_test_name("test uri: " + test_uri);
		LLURI uri(test_uri);
		ensure_equals("Port must be 443", uri.get().getPort(), 8443);
		ensure_equals("Host must be www.google.com", uri.get().getHost(), "www.google.com");
		ensure_equals("Scheme must be http", uri.get().getScheme(), "https");
		ensure_equals("Path must be '/caps/login.cgi'", uri.get().getPath(), "/caps/login.cgi");
	}

	DEF_TEST(6)
	{
		static String const test_uri = "https://www.google.com:8443/caps/login.cgi?blah=blub";
		set_test_name("test uri: " + test_uri);
		LLURI uri(test_uri);
		ensure_equals("Port must be 443", uri.get().getPort(), 8443);
		ensure_equals("Host must be www.google.com", uri.get().getHost(), "www.google.com");
		ensure_equals("Scheme must be http", uri.get().getScheme(), "https");
		ensure_equals("Path must be '/caps/login.cgi'", uri.get().getPath(), "/caps/login.cgi");
		ensure_equals("Query must be 'blah=blub'", uri.get().getQuery(), "blah=blub");
		ensure_equals("PathAndQuery must be '/caps/login.cgi?blah=blub'", uri.get().getPathAndQuery(), "/caps/login.cgi?blah=blub");
	}

	DEF_TEST(7)
	{
		static String const test_uri = "https://user:pass@www.google.com:8443/caps/login.cgi?blah=blub";
		set_test_name("test uri: " + test_uri);
		LLURI uri(test_uri);
		ensure_equals("UserInfo must be: 'user:pass'", uri.get().getUserInfo(), "user:pass");		
		ensure_equals("Port must be 443", uri.get().getPort(), 8443);
		ensure_equals("Host must be www.google.com", uri.get().getHost(), "www.google.com");
		ensure_equals("Scheme must be http", uri.get().getScheme(), "https");
		ensure_equals("Path must be '/caps/login.cgi'", uri.get().getPath(), "/caps/login.cgi");
		ensure_equals("Query must be 'blah=blub'", uri.get().getQuery(), "blah=blub");
		ensure_equals("PathAndQuery must be '/caps/login.cgi?blah=blub'", uri.get().getPathAndQuery(), "/caps/login.cgi?blah=blub");
	}

	DEF_TEST(8)
	{
		static String const test_uri = "https://user:pass@www.google.com:8443/caps/login.cgi?blah=blub";
		set_test_name("LLURI compare operators check");
		LLURI uri(test_uri);
		LLURI empty;

		ensure_not("op== must return false", uri == empty);
		ensure_not("op== must return false", empty == uri);

		ensure("op!= must return true", uri != empty);
		ensure("op!= must return true", empty != uri);

		ensure("op== must return true", empty == empty);
		ensure("op== must return true", uri == uri);

		ensure_not("op!= must return false", empty != empty);
		ensure_not("op!= must return false", uri != uri);

		ensure("op!= must return true", empty != test_uri);
		ensure_not("op== must return false", empty == test_uri);

		ensure_not("op!= must return false", uri != test_uri);
		ensure("op== must return true", uri == test_uri);
	}

	DEF_TEST(9)
	{
		static String const test_uri = "https://user:pass@www.google.com:8443/caps/login.cgi?blah=blub";
		set_test_name("LLURI parse and rebuild check");
		LLURI uri(test_uri);
		ensure_equals("test_uri and uri.to_string() have to be equal", uri.to_string(), test_uri);
	}
}

