#ifndef BOOST_NETWORK_URL_HPP_
#define BOOST_NETWORK_URL_HPP_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/network/url/tags.hpp>
#include <boost/network/url/traits/string.hpp>
#include <boost/network/url/basic_url.hpp>
#include <boost/network/url/http/url.hpp>

namespace boost { namespace network { namespace url {

    typedef basic_url<tags::default_> url;

    namespace http {
        typedef basic_url<tags::http> url;
    }

} // namespace url
} // namespace network
} // namespace boost

#endif

