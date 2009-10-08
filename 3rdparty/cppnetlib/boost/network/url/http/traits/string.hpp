#ifndef BOOST_NETWORK_URL_HTTP_TRAITS_STRING_HPP_
#define BOOST_NETWORK_URL_HTTP_TRAITS_STRING_HPP_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/network/url/traits/string.hpp>

namespace boost { namespace network { namespace url {

    namespace tags {
        struct http;
    }

    namespace traits {

        template <>
            struct string<tags::http> {
                typedef std::string type;
            };

    } // namespace traits

} // namespace url

} // namespace network

} // namespace boost

#endif

