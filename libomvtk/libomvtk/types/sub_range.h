// vim:et:st=4:ts=4:sts=4:
// Copyright (c) 2008,2009 by the OpenMetaverse Toolkit Library Team
// All rights reserved.
//
// - Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// - Neither the name of the OpenMetaverse Toolkit Library Team nor the names
//   of its contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE
#ifndef GUARD_LIBOMVTK_TYPES_BYTE_SUB_RANGE_H_INCLUDED
#define GUARD_LIBOMVTK_TYPES_BYTE_SUB_RANGE_H_INCLUDED

#if _MSC_VER > 1200
#    pragma once
#endif

#include "base_types.h"
#include "assert.h"
#include <iterator>
#include <boost/range.hpp>
#include <boost/mpl/and.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>

namespace omvtk
{
    template<BOOST_DEDUCED_TYPENAME T>
    struct always_true : boost::mpl::true_
    {
    };

    template<BOOST_DEDUCED_TYPENAME T, BOOST_DEDUCED_TYPENAME ContainerT>
    struct is_iterator_of
        : boost::mpl::or_<
            boost::is_same<BOOST_DEDUCED_TYPENAME ContainerT::iterator, T>,
            boost::is_same<BOOST_DEDUCED_TYPENAME ContainerT::const_iterator, T>
        >::type
    {

    };

    template<BOOST_DEDUCED_TYPENAME T>
    struct is_string_iterator
        : is_iterator_of<T, String>
    {
    };


    template
    <        
        typename ValueType, 
        template <typename> class AdditionalCondition = always_true 
    >
    struct sub_range
        : boost::sub_range<std::pair<ValueType const *,ValueType const *> > 
    {
    protected:
        typedef std::vector<Byte>::difference_type difference_type;
        typedef ValueType const * _iter_t;
    public:
        template<typename IteratorType>
        struct iterator_check
        {
            typedef std::iterator_traits<IteratorType> iter_traits;

            //Check that we got a raw pointer or a vector pointer
            typedef BOOST_DEDUCED_TYPENAME boost::mpl::or_< 
                boost::is_pointer<IteratorType>, 
                is_iterator_of<
                    IteratorType, 
                    std::vector<BOOST_DEDUCED_TYPENAME iter_traits::value_type> 
                >,
                AdditionalCondition<IteratorType>
            > vec_iter_or_pointer;


            //Check the iterator category (has to be random access iterator tag)
            typedef boost::is_same<
                BOOST_DEDUCED_TYPENAME iter_traits::iterator_category,
                std::random_access_iterator_tag
            > type_check;            

            // Check the size of the value type has to be Byte
            enum
            {                 
                value = 
                (
                    sizeof(BOOST_DEDUCED_TYPENAME iter_traits::value_type) == sizeof(ValueType) 
                    && type_check::value 
                    && vec_iter_or_pointer::value
                )
            };


        };

        typedef std::pair<ValueType const *,ValueType const *> range_pair;
        typedef boost::sub_range<range_pair> base;
        
        /// Create a empty byte range 
        sub_range()
            : base(_iter_t(0),_iter_t(0))
        {}

        /// create a sub_range
        template<typename IteratorT>
        sub_range(
                IteratorT it,
                IteratorT end        
            )
            : base(make_range(it, end))
        {
            BOOST_STATIC_ASSERT(iterator_check<IteratorT>::value);
        }

        difference_type size() const
        {
            if(base::empty())
            {
                return 0;
            }
            return base::size();
        }

    protected:
        template<typename IterT>
        ValueType const * Cast(IterT iter)
        {
            typedef ValueType const * ResultIter;
            return ResultIter(iter);
        }

        template<typename IterT>
        base make_range(
            IterT it, 
            IterT end
        )
        {
            if(it == end)
                return base(_iter_t(0),_iter_t(0));
            libomvtk_ensure(it < end);
            return base(Cast(&(*it)), Cast((&(*(it + (end - it) - 1))) + 1));
        }
    };

    typedef sub_range<
        Byte,
        is_string_iterator
    > byte_sub_range;
}

#endif //GUARD_LIBOMVTK_TYPES_BYTE_SUB_RANGE_H_INCLUDED
