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
#ifndef GUARD_LIBOMVTK_UTILS_LOCKED_PROPERTY_H_INCLUDED
#define GUARD_LIBOMVTK_UTILS_LOCKED_PROPERTY_H_INCLUDED

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

namespace omvtk
{
    template<typename ValueType>
    struct LockedProperty : boost::noncopyable
    {
        typedef boost::mutex Mutex;
        typedef boost::mutex::scoped_lock Lock;

        LockedProperty(Mutex & mutex, ValueType default_value)
        : boost::noncopyable()
        , m_value(default_value)
        , m_mutex(mutex)
        {}

        ~LockedProperty()
        {}

        ValueType operator()() const
        {
            Lock lock(m_mutex);
            ValueType value = m_value;
            return value;
        }

        void operator()(ValueType const & value)
        {
            Lock lock(m_mutex);
            m_value = value;
        }    

        operator ValueType () const
        {
            Lock lock(m_mutex);
            ValueType value = m_value;
            return value;
        }

        void operator=(ValueType const & value)
        {
            Lock lock(m_mutex);
            m_value = value;
        }
    protected:
        ValueType m_value;
        Mutex & m_mutex;
    };
}

#endif //GUARD_LIBOMVTK_UTILS_LOCKED_PROPERTY_H_INCLUDED

