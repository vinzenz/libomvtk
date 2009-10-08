#ifndef BOOST_NETWORK_URL_BASIC_URL_
#define BOOST_NETWORK_URL_BASIC_URL_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/spirit/home/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/home/phoenix.hpp>
#include <boost/range.hpp>

#include <boost/network/url/basic_url_fwd.hpp>
#include <boost/network/url/detail/parse_url.hpp>
#include <boost/network/url/url_concept.hpp>

namespace boost { namespace network { namespace url {

    template <class Tag>
        struct url_base {
            typedef typename traits::string<Tag>::type string_type;

            url_base(string_type const & url = string_type())            
                : 
                    raw_(url), 
                    parts_(), 
                    valid_(parse_url(raw_, parts_)) 
            { }

            url_base(const url_base & other)
                : 
                    raw_(other.raw_), 
                    parts_(other.parts_), 
                    valid_(other.valid_) 
            { }

            url_base & operator=(url_base other) {
                other.swap(*this);
                return *this; 
            }

            url_base & operator=(string_type const & url) {
                return *this = url_base(url);
            }

            void swap(url_base & other) {
                using std::swap;
                swap(other.raw_, raw_);
                swap(other.parts_, parts_);
                swap(other.valid_, valid_);
            }

            string_type protocol() const {
                return parts_.scheme;
            }

            string_type rest() const {
                return parts_.scheme_specific_part;
            }

            bool valid() const {
                return valid_;
            }

            bool operator==(url_base const & other) const {
                return (raw_ == other.raw_) && (parts_ == other.parts_) && (valid_ == other.valid_);
            }

            bool operator!=(url_base const & other) const {
                return !(*this == other);
            }

            protected:

            string_type raw_;
            detail::url_parts<Tag> parts_;
            bool valid_;
        };

    template <class Tag> 
        struct basic_url : url_base<Tag> {
            using url_base<Tag>::operator=;
            using url_base<Tag>::string_type;
            using url_base<Tag>::operator==;
            using url_base<Tag>::operator!=;
        };

    template <class Tag>
        inline 
        void 
        swap(basic_url<Tag> & left, basic_url<Tag> & right) {
            right.swap(left);
        }

    template <class Tag>
        inline 
        typename traits::string<Tag>::type 
        protocol(basic_url<Tag> const & url) {
            return url.protocol();
        }

    template <class Tag>
        inline 
        typename traits::string<Tag>::type 
        rest(basic_url<Tag> const & url) {
            return url.rest();
        }

    template <class Tag>
        inline 
        bool 
        valid(basic_url<Tag> const & url) {
            return url.valid();
        }

    // Check that the Url concept is met by the basic_url type.
    BOOST_CONCEPT_ASSERT((Url<basic_url<tags::default_> >));

} // namespace url

} // namespace network

} // namespace boost

#endif

