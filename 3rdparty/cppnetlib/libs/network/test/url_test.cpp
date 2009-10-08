
// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt of copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE URL Test
#include <boost/test/unit_test.hpp>
#include <boost/network/url.hpp>
#include <algorithm>

BOOST_AUTO_TEST_CASE(constructor_test) {
    using namespace boost::network::url;
    using std::string;
    url instance;
    instance = "http://www.boost.org/";
    BOOST_CHECK_EQUAL(protocol(instance), string("http"));
    BOOST_CHECK_EQUAL(rest(instance), string("//www.boost.org/"));
    BOOST_CHECK(valid(instance));
}

BOOST_AUTO_TEST_CASE(http_full_url_test) {
    using namespace boost::network::url;
    using std::string;

    http::url instance;
    instance = "http://user:password@www.boost.org/path?query#fragment";
    BOOST_CHECK_EQUAL(protocol(instance), string("http"));
    BOOST_CHECK_EQUAL(rest(instance), string("//user:password@www.boost.org/path?query#fragment"));
    BOOST_CHECK_EQUAL(user_info(instance), string("user:password"));
    BOOST_CHECK_EQUAL(host(instance), string("www.boost.org"));
    BOOST_CHECK_EQUAL(port(instance), 80u);
    BOOST_CHECK_EQUAL(path(instance), string("/path"));
    BOOST_CHECK_EQUAL(query(instance), string("query"));
    BOOST_CHECK_EQUAL(fragment(instance), string("fragment"));
    BOOST_CHECK(valid(instance));
}

BOOST_AUTO_TEST_CASE(http_simple_url_test) {
    using namespace boost::network::url;
    using std::string;

    http::url instance;
    instance = "http://www.boost.org/";
    BOOST_CHECK_EQUAL(protocol(instance), string("http"));
    BOOST_CHECK_EQUAL(rest(instance), string("//www.boost.org/"));
    BOOST_CHECK_EQUAL(user_info(instance), string());
    BOOST_CHECK_EQUAL(host(instance), string("www.boost.org"));
    BOOST_CHECK_EQUAL(port(instance), 80u);
    BOOST_CHECK_EQUAL(path(instance), string("/"));
    BOOST_CHECK_EQUAL(query(instance), string());
    BOOST_CHECK_EQUAL(fragment(instance), string());
    BOOST_CHECK(valid(instance));
}

BOOST_AUTO_TEST_CASE(https_simple_url_test) {
    using namespace boost::network::url;
    using std::string;

    http::url instance;
    instance = "https://www.boost.org/";
    BOOST_CHECK_EQUAL(protocol(instance), string("https"));
    BOOST_CHECK_EQUAL(port(instance), 443u);
}

BOOST_AUTO_TEST_CASE(http_with_port_test) {
    using namespace boost::network::url;
    using std::string;

    http::url instance;
    BOOST_CHECK(!valid(instance));
    instance = "http://www.boost.org:80/";
    BOOST_CHECK_EQUAL(host(instance), string("www.boost.org"));
    BOOST_CHECK_EQUAL(port(instance), 80u);
    BOOST_CHECK(valid(instance));
}

