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
#ifdef _MSC_VER
#    pragma warning(push)
#    pragma warning(disable: 4702)
#    pragma warning(disable: 4512)
#endif

#include "value.h"
#include "traits.h"

namespace omvtk
{
    LLSDValue::LLSDValue()
        : m_value(Undef())
        , m_current(LLSDValue::VT_UNDEF)
    {
    }

    LLSDValue::LLSDValue(LLSDValue const & o)
        : m_value(o.m_value)
        , m_current(o.m_current)
    {
    }

    LLSDValue::LLSDValue(Boolean v)
        : m_value(v)
        , m_current(LLSDValue::VT_BOOLEAN)
    {
    }

    LLSDValue::LLSDValue(Integer v)
        : m_value(v)
        , m_current(LLSDValue::VT_INTEGER)
    {
    }

    LLSDValue::LLSDValue(Real v)
        : m_value(v)
        , m_current(LLSDValue::VT_REAL)
    {
    }

    LLSDValue::LLSDValue(String const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_STRING)
    {
    }

    LLSDValue::LLSDValue(char const * v)
        : m_value(String(v ? v : ""))
        , m_current(LLSDValue::VT_STRING)
    {

    }

    LLSDValue::LLSDValue(URI const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_URI)
    {
    }

    LLSDValue::LLSDValue(UUID const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_UUID)
    {
    }

    LLSDValue::LLSDValue(Date const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_DATE)
    {
    }

    LLSDValue::LLSDValue(Binary const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_BINARY)
    {
    }

    LLSDValue::LLSDValue(Map const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_MAP)
    {
    }

    LLSDValue::LLSDValue(Array const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_ARRAY)
    {
    }

    LLSDValue::LLSDValue(Undef const & v)
        : m_value(v)
        , m_current(LLSDValue::VT_UNDEF)
    {
    }

    void LLSDValue::swap(LLSDValue & other)
    {
        m_value.swap(other.m_value);
        std::swap(m_current, other.m_current);
    }

    LLSDValue & LLSDValue::operator=(LLSDValue o)
    {
        swap(o);
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Boolean v)
    {
        m_current = VT_BOOLEAN;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Integer v)
    {
        m_current = VT_INTEGER;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Real v)
    {
        m_current = VT_REAL;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(String const & v)
    {
        m_current = VT_STRING;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(char const * v)
    {
        m_current = VT_STRING;
        m_value = String(v ? v : "");
        return *this;
    }

    LLSDValue & LLSDValue::operator=(URI const & v)
    {
        m_current = VT_URI;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(UUID const & v)
    {
        m_current = VT_UUID;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Date const & v)
    {
        m_current = VT_DATE;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Binary const & v)
    {
        m_current = VT_BINARY;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Map const & v)
    {
        m_current = VT_MAP;
        m_value = v;
        return *this;
    }

    LLSDValue & LLSDValue::operator=(Array const & v)
    {
        m_current = VT_ARRAY;
        m_value = v;
        return *this;
    }

    LLSDValue::operator bool() const
    {
        return m_current != VT_UNDEF;
    }

    bool LLSDValue::operator == (LLSDValue const & value) const
    {
        if(value.m_current == m_current)
        {
            switch(m_current)
            {
            case LLSDValue::VT_UNDEF:    
                return true;
            case LLSDValue::VT_BOOLEAN: 
                return boolean() == value.boolean();
            case LLSDValue::VT_INTEGER: 
                return integer() == value.integer();
            case LLSDValue::VT_REAL:    
                return real() == value.real();
            case LLSDValue::VT_STRING:  
                return string() == value.string();
            case LLSDValue::VT_UUID:    
                return uuid() == value.uuid();
            case LLSDValue::VT_URI:        
                return uri() == value.uri();
            case LLSDValue::VT_DATE:    
                return date() == value.date();
            case LLSDValue::VT_BINARY:    
                return binary() == value.binary();
            case LLSDValue::VT_ARRAY:    
                return array() == value.array();
            case LLSDValue::VT_MAP:        
                return map() == value.map();
            default:
                boost::throw_exception(IllegalStateException("Illegal LLSDValue::Types value detected"));
            }
        }
        return false;
    }

    bool LLSDValue::operator != (LLSDValue const & value) const
    {
        return !(*this == value);
    }

    LLSDValue::Types LLSDValue::type() const
    { 
        return m_current; 
    }

    void LLSDValue::clear()
    {
        m_current = LLSDValue::VT_UNDEF;
        m_value = Undef();
    }

    LLSDValue::Boolean LLSDValue::to_boolean() const
    {
        typedef detail::LLSDConverter<LLSDValue::Boolean> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::Integer LLSDValue::to_integer() const
    {
        typedef detail::LLSDConverter<LLSDValue::Integer> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::Real LLSDValue::to_real() const
    {
        typedef detail::LLSDConverter<LLSDValue::Real> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::String LLSDValue::to_string() const
    {
        typedef detail::LLSDConverter<LLSDValue::String> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::UUID    LLSDValue::to_uuid() const
    {
        typedef detail::LLSDConverter<LLSDValue::UUID> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::URI LLSDValue::to_uri() const
    {
        typedef detail::LLSDConverter<LLSDValue::URI> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::Date    LLSDValue::to_date() const
    {
        typedef detail::LLSDConverter<LLSDValue::Date> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::Binary LLSDValue::to_binary() const
    {
        typedef detail::LLSDConverter<LLSDValue::Binary> ConvT;
        return ConvT::convert(m_value, m_current);
    }

    LLSDValue::Boolean const & LLSDValue::boolean() const
    {
        return boost::any_cast<LLSDValue::Boolean const&>(m_value);
    }

    LLSDValue::Boolean & LLSDValue::boolean()
    {
        return boost::any_cast<LLSDValue::Boolean&>(m_value);
    }

    LLSDValue::Integer const & LLSDValue::integer() const
    {
        return boost::any_cast<LLSDValue::Integer const &>(m_value);
    }

    LLSDValue::Integer & LLSDValue::integer()
    {
        return boost::any_cast<LLSDValue::Integer&>(m_value);
    }

    LLSDValue::Real    const & LLSDValue::real() const
    {
        return boost::any_cast<LLSDValue::Real const &>(m_value);
    }

    LLSDValue::Real    & LLSDValue::real()
    {
        return boost::any_cast<LLSDValue::Real &>(m_value);
    }

    LLSDValue::String const & LLSDValue::string() const
    {
        return boost::any_cast<LLSDValue::String const &>(m_value);
    }

    LLSDValue::String & LLSDValue::string()
    {
        return boost::any_cast<LLSDValue::String &>(m_value);
    }

    LLSDValue::UUID    const & LLSDValue::uuid() const
    {
        return boost::any_cast<LLSDValue::UUID const &>(m_value);
    }

    LLSDValue::UUID    & LLSDValue::uuid()
    {
        return boost::any_cast<LLSDValue::UUID &>(m_value);
    }

    LLSDValue::URI const & LLSDValue::uri() const
    {
        return boost::any_cast<LLSDValue::URI const &>(m_value);
    }

    LLSDValue::URI & LLSDValue::uri()
    {
        return boost::any_cast<LLSDValue::URI &>(m_value);
    }

    LLSDValue::Date    const & LLSDValue::date() const
    {
        return boost::any_cast<LLSDValue::Date const &>(m_value);
    }

    LLSDValue::Date    & LLSDValue::date()
    {
        return boost::any_cast<LLSDValue::Date &>(m_value);
    }

    LLSDValue::Binary const & LLSDValue::binary() const
    {
        return boost::any_cast<LLSDValue::Binary const &>(m_value);
    }

    LLSDValue::Binary & LLSDValue::binary()
    {
        return boost::any_cast<LLSDValue::Binary &>(m_value);
    }

    LLSDValue::Array const & LLSDValue::array() const
    {
        return boost::any_cast<LLSDValue::Array const &>(m_value);
    }

    LLSDValue::Array & LLSDValue::array()
    {
        return boost::any_cast<LLSDValue::Array &>(m_value);
    }

    LLSDValue::Map const & LLSDValue::map() const
    {
        return boost::any_cast<LLSDValue::Map const &>(m_value);
    }

    LLSDValue::Map & LLSDValue::map()
    {
        return boost::any_cast<LLSDValue::Map &>(m_value);
    }

    LLSDValue::String LLSDValue::xml_encode() const
    {
        typedef detail::LLSDConverter<LLSDValue> ConvT;
         return ConvT::get_wrap(m_current).xml_encode(m_value);
    }
    
    LLSDValue::String LLSDValue::notation_encode() const
    {
        typedef detail::LLSDConverter<LLSDValue> ConvT;
        return ConvT::get_wrap(m_current).notation_encode(m_value);
    }

    void LLSDValue::binary_encode(Binary & out) const
    {
        typedef detail::LLSDConverter<LLSDValue> ConvT;
        return ConvT::get_wrap(m_current).binary_encode(out, m_value);
    }

    /// Encodes value as LLSD+Binary
    LLSDValue::Binary LLSDValue::binary_encode() const
    {
        Binary b;
        binary_encode(b);
        return b;
    }
#ifndef DOXYGEN_SHOULD_SKIP_THIS

    void LLSDValue::xml_decode(Types typeID, byte_sub_range const & sr)
    {
        typedef detail::LLSDConverter<LLSDValue> ConvT;
        m_value = ConvT::get_wrap(typeID).xml_decode(sr);
        m_current = typeID;
    }

    void LLSDValue::notation_decode(Types typeID, byte_sub_range const & sr)
    {
        typedef detail::LLSDConverter<LLSDValue> ConvT;
        m_value = ConvT::get_wrap(typeID).notation_decode(sr);
        m_current = typeID;
    }

    void LLSDValue::binary_decode(Types typeID, byte_sub_range const & sr)
    {
        typedef detail::LLSDConverter<LLSDValue> ConvT;
        m_value = ConvT::get_wrap(typeID).binary_decode(sr);
        m_current = typeID;
    }

#endif
}

#ifdef _MSC_VER
#    pragma warning(pop)
#endif

