#ifndef BOOST_NETWORK_URL_URL_CONCEPT_HPP_
#define BOOST_NETWORK_URL_URL_CONCEPT_HPP_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/concept_check.hpp>

namespace boost { namespace network { namespace url {

    template <class U>
        struct Url : DefaultConstructible<U>, EqualityComparable<U> {
            typedef typename U::string_type string_type;

            BOOST_CONCEPT_USAGE(Url)
            {
                U url_(url); // copy constructable
                U temp;
                swap(temp, url_); // swappable
                string_type protocol_ = protocol(url); // support protocol function
                string_type rest_ = rest(url);
                bool valid_ = valid(url);
                valid_ = false;
            }

            private:
            U url;
        };

} // namespace url

} // namespace network

} // namespace boost

#endif

