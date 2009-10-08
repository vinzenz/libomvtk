#ifndef BOOST_NETWORK_URL_HTTP_DETAIL_PARSE_SPECIFIC_HPP_
#define BOOST_NETWORK_URL_HTTP_DETAIL_PARSE_SPECIFIC_HPP_

// Copyright 2009 Dean Michael Berris.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt of copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/network/url/http/detail/url_parts.hpp>
#include <boost/network/url/detail/parse_url.hpp>

namespace boost { namespace network { namespace url { 

    namespace detail {

        template <>
            bool parse_specific<
                traits::string<tags::http>::type,
                tags::http
                    >(
                            traits::string<tags::http>::type & range,
                            url_parts<tags::http> & parts
                     ) 
            {
                // Require that parts.scheme is either http or https
                if (parts.scheme.size() < 4)
                    return false;
                if (parts.scheme.substr(0, 4) != "http")
                    return false;
                if (parts.scheme.size() == 5) {
                    if (parts.scheme[4] != 's')
                        return false;
                } else if (parts.scheme.size() > 5)
                    return false;
                
                using spirit::qi::parse;
                using spirit::qi::lit;
                using spirit::ascii::char_;
                using spirit::ascii::space;
                using spirit::qi::lexeme;
                using spirit::qi::uint_;
                using fusion::tie;
                
                typedef traits::string<tags::http>::type string_type;
                typedef range_iterator<string_type>::type iterator;

                iterator start_ = begin(range);
                iterator end_ = end(range);
                fusion::tuple<
                    optional<string_type> &,
                    string_type &,
                    optional<uint32_t> &,
                    optional<string_type> &,
                    optional<string_type> &,
                    optional<string_type> &
                        > result =
                        tie(
                                parts.user_info,
                                parts.host,
                                parts.port,
                                parts.path,
                                parts.query,
                                parts.fragment
                           );

                bool ok = parse(
                        start_, end_,
                        (
                         lit("//")
                         >> -lexeme[
                            *(char_ - '@')
                            >> '@'
                            ]
                         >> +(char_ - char_("/:"))
                         >> -lexeme[':' >> uint_]
                         >> -lexeme['/' >> *(char_ - '?')]
                         >> -lexeme['?' >> *(char_ - '#')]
                         >> -lexeme['#' >> *char_]
                        ),
                        result
                        );

                return ok && start_ == end_;
            }

    } // namespace detail

} // namespace url

} // namespace network

} // namespace boost

#endif

