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
#include "lluuid.h"
#include "assert.h"
#include <sstream>

namespace // local visibility only so we can use an arbitary name
{
    boost::uuid fromSubRange(omvtk::byte_sub_range const & b)
    {
        boost::uuid uuid;        
        libomvtk_ensure(b.size() == 16);
        uuid.assign(b.begin(), b.end());
        return uuid;
    }

    boost::uuid fromString(omvtk::String const & str)
    {
        std::istringstream istr(str);
        boost::uuid u;
        istr >> u;
        return u;
    }
}

namespace omvtk
{
    /// static zero uuid instance
    LLUUID const LLUUID::Zero = LLUUID();

    /// Default constructor initializes Zero LLUUID
    LLUUID::LLUUID()
        : m_data()
    {        
    }


    /// Initialize from an internal object 
    LLUUID::LLUUID(value_type const & val)
        : m_data(val)
    {
    }


    /// Initialize from string representation
    LLUUID::LLUUID(String const & str)
        : m_data(fromString(str))
    {
    }

    /// Initialize the LLUUID from a byte sub range (avoids copies)
    LLUUID::LLUUID(byte_sub_range const & sr)
        : m_data(fromSubRange(sr))
    {

    }

    /// Initialize from Buffer
    LLUUID::LLUUID(ByteBuffer const & buf)
        : m_data(fromSubRange(byte_sub_range(buf.begin(), buf.end())))
    {
    }


    /// Copy constructor
    LLUUID::LLUUID(LLUUID const & other)
        : m_data(other.m_data)
    {
    }


    /// Destructor
    LLUUID::~LLUUID()
    {
    }


    /// Assignment operator
    LLUUID & LLUUID::operator=(LLUUID other)
    {
        swap(other);
        return *this;
    }


    /// equal compare operator
    bool LLUUID::operator == (const LLUUID& uuid) const
    {
        return m_data == uuid.m_data;
    }


    /// not equal compare operator 
    bool LLUUID::operator != (const LLUUID& uuid) const
    {
        return m_data != uuid.m_data;
    }


    /// less than compare operator
    bool LLUUID::operator <  (const LLUUID& uuid) const
    {
        return m_data < uuid.m_data;
    }


    /// less than or equal compare operator
    bool LLUUID::operator <= (const LLUUID& uuid) const
    {
        return m_data <= uuid.m_data;
    }


    /// greater than compare operator
    bool LLUUID::operator >  (const LLUUID& uuid) const
    {
        return m_data > uuid.m_data;
    }


    /// greater than or equal compare operator
    bool LLUUID::operator >= (const LLUUID& uuid) const
    {
        return m_data >= uuid.m_data;
    }

    void LLUUID::swap(LLUUID & other)
    {
        m_data.swap(other.m_data);
    }

    /// Whether the current instance is a zero uuid
    bool LLUUID::is_zero() const
    {
        return m_data.is_nil();
    }


    /// Converts to string representation
    String LLUUID::to_string() const
    {
        std::ostringstream str;
        str << m_data;
        return str.str();
    }


    /// Converts to binary buffer
    ByteBuffer LLUUID::to_binary() const
    {
        return ByteBuffer(m_data.begin(), m_data.end());        
    }


    /// returns an internal instance
    LLUUID::value_type & LLUUID::get()
    {
        return m_data;
    }


    /// returns an internal instance
    LLUUID::value_type const & LLUUID::get() const
    {
        return m_data;
    }

}

