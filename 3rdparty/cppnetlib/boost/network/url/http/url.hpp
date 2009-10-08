#ifndef BOOST_NETWORK_URL_HTTP_URL_HPP_
#define BOOST_NETWORK_URL_HTTP_URL_HPP_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/fusion/tuple.hpp>

#include <boost/network/url/tags.hpp>
#include <boost/network/url/basic_url_fwd.hpp>
#include <boost/network/url/http/traits/string.hpp>
#include <boost/network/url/http/detail/parse_specific.hpp>
#include <boost/network/url/http/detail/url_parts.hpp>
#include <boost/network/url/http/url_concept.hpp>

namespace boost { namespace network { namespace url {

    template <>
        struct basic_url<tags::http> : url_base<tags::http> {
            using url_base<tags::http>::string_type;
            using url_base<tags::http>::operator=;

            string_type host() const {
                return parts_.host;
            }

            uint32_t port() const {
                return parts_.port ? *parts_.port : 
                    (parts_.scheme == "https" ? 443u : 80u);
            }

            string_type path() const {
                return string_type("/") + (parts_.path ? *parts_.path : string_type());
            }

            string_type query() const {
                return parts_.query ? *parts_.query : string_type();
            }

            string_type fragment() const {
                return parts_.fragment ? *parts_.fragment : string_type();
            }

            string_type user_info() const {
                return parts_.user_info ? *parts_.user_info : string_type();
            }

        };

    inline 
        basic_url<tags::http>::string_type 
        host(basic_url<tags::http> const & url) {
            return url.host();
        }

    inline
        uint32_t
        port(basic_url<tags::http> const & url) {
            return url.port();
        }

    inline
        basic_url<tags::http>::string_type
        path(basic_url<tags::http> const & url) {
            return url.path();
        }

    inline 
        basic_url<tags::http>::string_type
        query(basic_url<tags::http> const & url) {
            return url.query();
        }

    inline 
        basic_url<tags::http>::string_type
        fragment(basic_url<tags::http> const & url) {
            return url.fragment();
        }

    inline
        basic_url<tags::http>::string_type
        user_info(basic_url<tags::http> const & url) {
            return url.user_info();
        }

    BOOST_CONCEPT_ASSERT((HttpUrl<basic_url<tags::http> >));

} // namespace url

} // namespace network

} // namespace boost

#endif

