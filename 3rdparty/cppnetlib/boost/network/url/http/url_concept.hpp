#ifndef BOOST_NETWORK_URL_HTTP_URL_CONCEPT_HPP_
#define BOOST_NETWORK_URL_HTTP_URL_CONCEPT_HPP_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/concept_check.hpp>
#include <boost/network/url/url_concept.hpp>

namespace boost { namespace network { namespace url {

    template <class U>
        struct HttpUrl : Url<U> {
            typedef typename U::string_type string_type;

            BOOST_CONCEPT_USAGE(HttpUrl)
            {
                string_type user_info_ = user_info(url);
                string_type host_ = host(url);
                uint32_t port_ = port(url);
                port_ = 0u;
                string_type path_ = path(url);
                string_type query_ = query(url);
                string_type fragment_ = fragment(url);
            }

            private:
            U url;
        };

} // namespace url

} // namespace network

} // namespace boost

#endif


